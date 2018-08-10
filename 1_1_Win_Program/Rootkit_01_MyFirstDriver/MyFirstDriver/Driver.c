﻿#include <ntddk.h>

VOID DriverUnload(PDRIVER_OBJECT objDriver)
{
	// 避免编译器关于未引用参数的警告
	UNREFERENCED_PARAMETER(objDriver);

	// 什么也不做，只打印一行字符串
	DbgPrint("My Dirver is unloading...");
}

NTSTATUS DriverEntry(PDRIVER_OBJECT objDriver, PUNICODE_STRING strRegPath)
{
	// 避免编译器关于未引用参数的警告
	UNREFERENCED_PARAMETER(strRegPath);

	// 如果编译方式为Debug，则插入一个INT 3指令，方便我们调试
#ifdef DBG
	_asm int 3;
#endif

	// 打印一行字符串，并注册驱动卸载函数，以便于驱动卸载
	DbgPrint("My First Dirver!");
	objDriver->DriverUnload = DriverUnload;

	return STATUS_SUCCESS;
}