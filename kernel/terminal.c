#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "./terminal.h"

const size_t VGA_WIDTH = 80;
const size_t VGA_HEIGHT = 25;

size_t terminal_row;
size_t terminal_column;
uint8_t terminal_color;
uint8_t terminal_break_row_condition;
uint16_t* terminal_buffer;

/*
	private functions
*/

inline uint8_t __vga_entry_color(enum vga_color fg, enum vga_color bg)
{
	return fg | bg << 4;
}

inline uint16_t __vga_entry(unsigned char uc, uint8_t color)
{
	return (uint16_t) uc | (uint16_t) color << 8;
}

void __terminal_putentryat(char c, uint8_t color, size_t x, size_t y)
{
	const size_t index = y * VGA_WIDTH + x;
	terminal_buffer[index] = __vga_entry(c, color);
}

void __terminal_putchar(char c)
{
	__terminal_putentryat(c, terminal_color, terminal_column, terminal_row);

	if (++terminal_column == VGA_WIDTH)
	{
		terminal_column = 0;

		if (++terminal_row == VGA_HEIGHT)
		{
			terminal_row += 1;
		}
	}
}

/*
	public functions
*/

void terminal_initialize(void)
{
	terminal_row = 0;
	terminal_column = 0;
	terminal_color = __vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
	terminal_break_row_condition = BREAK_ROW_ON_WORD;
	terminal_buffer = (uint16_t*) 0xB8000;
	for (size_t y = 0; y < VGA_HEIGHT; y++) {
		for (size_t x = 0; x < VGA_WIDTH; x++) {
			const size_t index = y * VGA_WIDTH + x;
			terminal_buffer[index] = __vga_entry(' ', terminal_color);
		}
	}
}

void terminal_scroll_down()
{
	for (size_t y = 1; y < VGA_HEIGHT; ++y)
	for (size_t x = 0; x < VGA_WIDTH; ++x)
	{
		const size_t up_one_row_index = (y-1) * VGA_WIDTH + x;
		const size_t index = y * VGA_WIDTH + x;

		terminal_buffer[up_one_row_index] = terminal_buffer[index];
	}

	terminal_row -= 1;
}

void terminal_setcolor(uint8_t color)
{
	terminal_color = color;
}

// NOTE(Alan): This does not escape any trailing white spaces, it probably shouldn't format the input in any way (other than breaking rows)
void terminal_writestring(const char* data)
{
	size_t size = strlen(data);
	for (size_t i = 0; i < size; i++)
	{
		if (terminal_break_row_condition == BREAK_ROW_ON_WORD)
		{
			bool word_contains_characters = false;
			size_t j = 0;
			while (true)
			{
				if (j >= VGA_WIDTH)
				{
					break;
				}

				if (i + j >= size)
				{
					break;
				}

				if (data[i + j] == '\n' || data[i + j] == '\n' || data[i + j] == ' ')
				{
					break;
				}

				word_contains_characters = true;

				++j;
			}

			if (word_contains_characters)
			{
				size_t chars_left_in_row = VGA_WIDTH - terminal_column % VGA_WIDTH;

				if (j > chars_left_in_row)
				{
					terminal_row += 1;
					terminal_column = 0;
					--i;
				}
			}
		}
		
		switch (data[i])
		{
			case ' ':
			{
				if (terminal_column > 0)
				{
					__terminal_putchar(data[i]);
				}
				
				break;
			}
			case '\n':
			{
				terminal_row += 1;
				terminal_column = 0;

				break;
			}
			case '\t':
			{
				terminal_column += 4;

				if (terminal_column >= VGA_WIDTH)
				{
					terminal_row += 1;
					terminal_column = 0;
				}

				break;
			}
			default:
			{
				__terminal_putchar(data[i]);
				break;
			}
		}

		if (terminal_row + 1 >= VGA_HEIGHT)
		{
			terminal_scroll_down();
		}
	}
}

void terminal_writenumber(const size_t number)
{
  	char buffer [33];

  	const char * c = itoa(number, buffer, 10);

	terminal_writestring(c);
}