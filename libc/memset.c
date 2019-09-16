void *memset(void *BufferPointer, int Value, size_t Size)
{
	unsigned char *Buffer = (unsigned char *)BufferPointer;
	for (size_t Index = 0; Index < Size; ++Index)
	{
		Buffer[Index] = (unsigned char)Value;
	}
	return BufferPointer;
}