#include "image.h"

hsb rgb2hsb(rgb in)
{
	hsb        out;
	float      min, max, delta;

	min = (in.r < in.g) ? in.r : in.g;
	min = min < in.b ? min : in.b;

	max = in.r > in.g ? in.r : in.g;
	max = max > in.b ? max : in.b;

	out.b = max / 255.0;                                // v
	delta = max - min;
	if (max > 0.0) { // NOTE: if Max is == 0, this divide would cause a crash
		out.s = (delta / max);                  // s
	}
	else {
		// if max is 0, then r = g = b = 0 // s = 0, h is undefined
		out.s = 0.0;
		out.h = 0.0;                            // its now undefined
		return out;
	}

	if (delta == 0) {
		out.h = 0.0; return out;
	}

	if (in.r >= max)                           // > is bogus, just keeps compilor happy
		out.h = 60.0 * (in.g - in.b) / delta;        // between yellow & magenta
	else if (in.g >= max)
		out.h = 120.0 + 60.0 * (in.b - in.r) / delta;  // between cyan & yellow
	else
		out.h = 240.0 + 60.0 * (in.r - in.g) / delta;  // between magenta & cyan

	if (out.h < 0.0)
		out.h += 360.0;

	return out;
}

rgb hsb2rgb(hsb in)
{
	float      p, q, t, f;
	int        i;
	rgb        out;

	if (in.s <= 0.0) {       // < is bogus, just shuts up warnings
		out.r = in.b; out.g = in.b; out.b = in.b;
	}
	else {
		if (in.h >= 360.0) in.h = 0.0;
		else in.h = in.h / 60.0;
		i = (int)truncf(in.h);
		f = in.h - i;
		p = in.b * (1.0 - in.s);
		q = in.b * (1.0 - (in.s * f));
		t = in.b * (1.0 - (in.s * (1.0 - f)));

		switch (i) {
		case 0:
			out.r = in.b;
			out.g = t;
			out.b = p;
			break;
		case 1:
			out.r = q;
			out.g = in.b;
			out.b = p;
			break;
		case 2:
			out.r = p;
			out.g = in.b;
			out.b = t;
			break;
		case 3:
			out.r = p;
			out.g = q;
			out.b = in.b;
			break;
		case 4:
			out.r = t;
			out.g = p;
			out.b = in.b;
			break;
		case 5:
		default:
			out.r = in.b;
			out.g = p;
			out.b = q;
			break;
		}
	}
	out.r *= 255; out.g *= 255; out.b *= 255;
	out.r = (out.r > 255) ? 255 : (out.r < 0) ? 0 : out.r;
	out.g = (out.g > 255) ? 255 : (out.g < 0) ? 0 : out.g;
	out.b = (out.b > 255) ? 255 : (out.b < 0) ? 0 : out.b;

	return out;
}

ycbcr rgb2ycbcr(rgb in)
{
	/*
	  Y   =  0.25579 * R + 0.50216 * G + 0.09752 * B + 16   
	  Cr  =  0.43734 * R - 0.36621 * G - 0.07112 * B + 128   
	  Cb = -0.16073 * R - 0.31555 * G + 0.47628 * B + 128
	*/
	ycbcr out;

	out.y = 0.25579*in.r + 0.50216*in.g + 0.09752*in.b + 16.0;
	out.cr = 0.43734 * in.r - 0.36621 * in.g - 0.07112 * in.b + 128.0;
	out.cb = -0.16073 * in.r - 0.31555 * in.g + 0.47628 * in.b + 128.0;
	return out;
}

rgb ycbcr2rgb(ycbcr in)
{
	/*
	  R  = 1.164(Y-16) + 1.596(Cr-128)    
	  G  = 1.164(Y-16) - 0.813(Cr-128) - 0.391(Cb-128)  
	  B  = 1.164(Y-16) + 2.018(Cb-128)
	*/
	rgb out;

	out.r = 1.164 * (in.y - 16.0) + 1.596 * (in.cr - 128.0);
	out.g = 1.164 * (in.y - 16.0) - 0.813 * (in.cr - 128.0) - 0.391 * (in.cb - 128.0);
	out.b = 1.164 * (in.y - 16.0) + 2.018 * (in.cb - 128.0);

	out.r = (out.r > 255) ? 255 : (out.r < 0) ? 0 : out.r;
	out.g = (out.g > 255) ? 255 : (out.g < 0) ? 0 : out.g;
	out.b = (out.b > 255) ? 255 : (out.b < 0) ? 0 : out.b;

	return out;
}