/**
 * desc: 
 * auth: chenxiaobin
 * data: 2015-10-22
 */

#ifndef _XERENDERFORMAT_H_
#define _XERENDERFORMAT_H_

enum EPixelFormat {
	EPixelFormatUnknow,
	EPixelFormatL8, // 1 byte pixel format, 1 byte luminance
	EPixelFormatL8A8, // 2 byte pixel format, 1 byte luminance, 1 byte alpha
	EPixelFormatR8G8B8, // 24-bit pixel format, 8 bits for red, green and blue.
	EPixelFormatR8G8B8A8 // 32-bit pixel format, 8 bits for red, green, blue and alpha.
};

#endif //_XERENDERFORMAT_H_
