#Error
#write: effective gid does not match group of /dev/pts/2
#https://bugs.launchpad.net/ubuntu/+source/util-linux/+bug/2064685
sudo chmod 02755 /usr/bin/write.ul
sudo chown root:tty /usr/bin/write.ul
