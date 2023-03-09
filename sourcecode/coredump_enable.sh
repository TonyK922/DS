# enable coredump for debug
# 注意此脚本不能运行，而应该按照如下步骤实施

#step 1 vim /etc/profile, 在末尾添加如下代码
echo "enable coredump file"
ulimit -c unlimited 
echo 0 > /proc/sys/kernel/core_uses_pid
echo "/data/core_%e_%p" > /proc/sys/kernel/core_pattern

#step 2  使之生效
source /etc/profile

#step 3 查看结果，如果输出ulimited，即为成功
ulimit -c