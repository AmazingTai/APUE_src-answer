
void test_lseek_read_write()
{
    M_TRACE("---------  Begin test_lseek_read_write()  ---------\n");
    int fd=My_open_with_mode("test",O_RDWR|O_TRUNC|O_CREAT,S_IRUSR|S_IWUSR);  // 读写打开，并截断
    if(-1==fd)  return; // 文件打开失败
    char read_buffer[20];
    char write_buffer[10];

    strcpy(write_buffer,"123456789"); // write_buffer 填充数字

    My_read(fd,read_buffer,20); // 读文件，期望读 20 个字节
    My_write(fd,write_buffer,10);// 写文件，期望写 10 个字节
    My_read(fd,read_buffer,20);// 读文件，期望读 20 个字节
    My_lseek(fd,0,SEEK_SET);// 定位文件到头部
    My_read(fd,read_buffer,20);// 读文件，期望读 20 个字节
    My_lseek(fd,10,SEEK_END);// 定位文件到尾部之后的 10 个字节
    My_read(fd,read_buffer,20);// 读文件，期望读 20 个字节
    My_write(fd,write_buffer,10);// 写文件，期望写 10 个字节
    My_read(fd,read_buffer,20);// 读文件，期望读 20 个字节
    My_lseek(fd,0,SEEK_SET);// 定位文件到头部
    My_read(fd,read_buffer,20);// 读文件，期望读 20 个字节
    My_read(fd,read_buffer,20);// 读文件，期望读 20 个字节
    close(fd);
    M_TRACE("---------  End test_lseek_read_write()  ---------\n\n");

}
	

	测试序列为：
	- 开始文件为空，所以读取20个字节的`read`只读取0
	- 写入文件10个字节
	- 读取文件。此时读和写共享一个当前文件偏移。而且当前文件偏移被`write`置于文件结尾。此时读取0个字节
	- 执行`lseek`将当前文件偏移量重置到文件开头，返回0（新的文件偏移量）
	- 读取文件，只能读取10个字节（因为文件此时就10个字节）
	- 执行`lseek`将文件偏移量放到文件末尾之后的10个字节，返回20（新的文件偏移量）
	- 读取文件。此时当前文件偏移被置于文件结尾。此时读取0个字节
	- 写入文件10个字节
	- 读取文件。此时当前文件偏移被`write`置于文件结尾。此时读取0个字节
	- 执行`lseek`将当前文件偏移量重置到文件开头，返回0（新的文件偏移量）
	- 读取文件，读取20个字节（因为文件结尾的偏移是30个字节）。空洞部分读取的结果都是 0 
	- 读取文件，只能读取10个字节（因为文件结尾的偏移是30个字节）