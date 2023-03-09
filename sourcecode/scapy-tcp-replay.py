#!/usr/bin/env python3
# -*- coding: utf-8 -*-
# author:      hyman
# file:        scapy-tcp-replay.py
# update_time: 8/5/22 4:53 PM

# 利用wireshark导出干净的数据包流, wireshark 页面过滤条件
# (tcp.stream eq 0) && !(tcp.analysis.flags)

import argparse
import time
from scapy.all import *
from scapy.layers.inet import TCP
from scapy.utils import PcapReader
import socket


def show_diff(raw1, raw2):
    def b2h(b):
        return " ".join([hex(j)[2:].rjust(2, '0') for j in b])

    def b2a(b):
        return ''.join([chr(k) if ord(' ') <= k <= ord('~') else '.' for k in b])

    if raw1 is None:
        parts = len(raw2) // 16
        if len(raw2) % 16 != 0:
            parts += 1
        for i in range(parts):
            print("{}  || {:23}  {:23} |{:16}| <0x{}> {:23}  {:23} |{:16}|".format(
                "!!=",
                "   " * 8 - 1,
                "   " * 8 - 1,
                " " * 16,
                hex(i * 16)[2:].rjust(8, '0'),
                b2h(raw2[i * 16: i * 16 + 8]),
                b2h(raw2[i * 16 + 8: i * 16 + 16]),
                b2a(raw2[i * 16: i * 16 + 16])
            ))
    if raw2 is None:
        parts = len(raw1) // 16
        if len(raw1) % 16 != 0:
            parts += 1
        for i in range(parts):
            print("{}  || {:23}  {:23} |{:16}| <0x{}> {:23}  {:23} |{:16}|".format(
                "!!=",
                b2h(raw1[i * 16: i * 16 + 8]),
                b2h(raw1[i * 16 + 8: i * 16 + 16]),
                b2a(raw1[i * 16: i * 16 + 16]),
                hex(i * 16)[2:].rjust(8, '0'),
                "   " * 8 - 1,
                "   " * 8 - 1,
                " " * 16,
            ))

    if raw2 and raw1:
        parts = len(raw1) // 16
        if len(raw1) % 16 != 0:
            parts += 1
        for i in range(parts):
            print("{}  || {:23}  {:23} |{:16}| <0x{}> {:23}  {:23} |{:16}|".format(
                "  " if (raw1[i * 16: i * 16 + 16] == raw2[i * 16: i * 16 + 16]) else "!=",
                b2h(raw1[i * 16: i * 16 + 8]),
                b2h(raw1[i * 16 + 8: i * 16 + 16]),
                b2a(raw1[i * 16: i * 16 + 16]),
                hex(i * 16)[2:].rjust(8, '0'),
                b2h(raw2[i * 16: i * 16 + 8]),
                b2h(raw2[i * 16 + 8: i * 16 + 16]),
                b2a(raw2[i * 16: i * 16 + 16])
            ))


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("-c", "--connect", help="server host")
    parser.add_argument("port", help="server port", type=int)
    parser.add_argument("filepath", help="pcap file", type=str)
    if len(sys.argv) == 1:
        parser.print_help()
        print("examples: python scapy-replay-tcp.py -c 127.0.0.1 2404 xxx.pcap")
        exit()
    args = parser.parse_args()
    if "pcap" not in args.filepath:
        print("not find pcap file")
        exit(1)

    if args.connect:
        client = ClientTcpReplay(
            args.filepath, args.connect,
            args.port)
        client.start()
    else:
        server = ServerTcpReplay(args.filepath, args.port)
        server.start()


class ClientTcpReplay:
    def __init__(self, filepath, host, port):
        print("client tcp replay", host, port, filepath)
        self.packages = PcapReader(filepath)
        self.host = host
        self.port = port
        pass

    def start(self):
        conn = socket.socket()
        conn.connect((self.host, self.port))
        print("connect server:", conn.getpeername())
        t = None
        no=0
        for i in self.packages:
            no +=1
            print("{:<5} {}".format(no, datetime.fromtimestamp(i.time) ))
            if t:
                time.sleep(i.time - t)
            t = i.time
            tcp = i[TCP]
            if len(tcp.payload) <= 0 or isinstance(tcp.payload, Padding):
                continue

            if tcp.dport == self.port:
                conn.send(bytes(tcp.payload))
                print("send: {}|{}|{} -- {}".format(tcp.seq, tcp.ack, len(tcp.payload), tcp.payload))
            else:
                data = conn.recv(len(tcp.payload))
                print("recv: {}|{}|{} -- {}".format(tcp.seq, tcp.ack, len(tcp.payload), tcp.payload))
                if data != bytes(tcp.payload):
                    print("server error, pcap vs socket")
                    show_diff(bytes(tcp.payload), data)
                    exit(1)
        conn.close()


class ServerTcpReplay:
    def __init__(self, filepath, port):
        print("server tcp replay", port, filepath)
        self.packages = PcapReader(filepath)
        self.port = port
        self.server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.server.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        self.server.bind(("0.0.0.0", port))
        self.server.listen(1)

    def start(self):
        conn, addr = self.server.accept()
        print("accept client:", conn.getpeername())
        t = None
        no = 0
        for i in self.packages:
            no +=1
            print("{:<5} {}".format(no, datetime.fromtimestamp(i.time) ))
            if t:
                time.sleep(i.time - t)
            t = i.time
            tcp = i[TCP]
            if len(tcp.payload) <= 0 or isinstance(tcp.payload, Padding):
                continue
            if tcp.sport == self.port:
                conn.send(bytes(tcp.payload))
                print("send: {}|{}|{} -- {}".format(tcp.seq, tcp.ack, len(tcp.payload), tcp.payload))
            else:
                data = conn.recv(len(tcp.payload))
                print("recv: {}|{}|{} -- {}".format(tcp.seq, tcp.ack, len(tcp.payload), tcp.payload))
                if data != bytes(tcp.payload):
                    print("server error, pcap vs socket")
                    show_diff(bytes(tcp.payload), data)
                    exit(1)
        time.sleep(1)
        conn.close()
        self.server.close()


if __name__ == "__main__":
    main()
    # server = ServerTcpReplay(
    #     "/mnt/t7/22-08-电科院电力协议进场调试/08-03-下午测试/104协议/104,4个操作的透传,正确传输..pcap", 2404)
    # client = ClientTcpReplay(
    #     "/mnt/t7/22-08-电科院电力协议进场调试/08-03-下午测试/104协议/104,4个操作的透传,正确传输..pcap", "127.0.0.1",
    #     2404)
    # Thread(target=server.start).start()
    # time.sleep(1)
    # client.start()
