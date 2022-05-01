#pragma once

enum Align
{
	AlignLeft				= 0x01,
	AlignHorizontalCenter	= 0x02,
	AlignRight				= 0x04,
	AlignTop				= 0x10, 
	AlignVerticalCenter		= 0x20,
	AlignBottom				= 0x40,
	
	AlignLeftTop			= AlignLeft | AlignTop,
	AlignLeftCenter			= AlignLeft | AlignVerticalCenter,
	AlignLeftBottom			= AlignLeft | AlignBottom,

	AlignCenterTop			= AlignHorizontalCenter | AlignTop,
	AlignCenterCenter		= AlignHorizontalCenter | AlignVerticalCenter,
	AlignCenterBottom		= AlignHorizontalCenter | AlignBottom,

	AlignRightTop			= AlignRight | AlignTop,
	AlignRightCenter		= AlignRight | AlignVerticalCenter,
	AlignRightBottom		= AlignRight | AlignBottom,

	AlignNone				= AlignLeftTop
};