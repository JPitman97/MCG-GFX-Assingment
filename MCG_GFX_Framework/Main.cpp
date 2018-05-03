#include <cmath>
#include "MCG_GFX_Lib.h"
#include <iostream>

void initializeWindow();
void showSquare(int width, int height);
void showTranslatedSquare(int width, int height, int xOffset, int yOffset);
void showCircle(int cSize);
void showFullCircle(int fCSize);
void showTriangle();
void showLine(int x0, int y0, int x1, int y1);
void showfake3D(int width, int height, int xOffset, int yOffset);

//!!!Global Variables!!!
const glm::ivec2 windowSize(640, 480);
const glm::vec2 centerX(windowSize.x / 2, 0);
const glm::vec2 centerY(0, windowSize.y / 2);
const glm::ivec3 color(0, 0, 255);
const glm::ivec3 color2(255, 0, 0);

int main(int argc, char *argv[])
{
	std::cout << "Please choose an option (Please close and re-open to view new choices)" << std::endl;
	std::cout << "1) Square" << std::endl;
	std::cout << "2) Square with Matrix Transformation" << std::endl;
	std::cout << "3) Circle (Not filled in)" << std::endl;
	std::cout << "4) Circle (Filled in)" << std::endl;
	std::cout << "5) Triangle" << std::endl;
	std::cout << "6) Bresenham's Line" << std::endl;
	std::cout << "7) Fake 3D Square/Rectangle (Negative translation numbers will cause lines to disappear)" << std::endl;

	int choice;
	std::cin >> choice;

	switch (choice)
	{
	case 1:
		std::cout << "Please enter the width: ";
		int w;
		std::cin >> w;
		std::cout << "Please enter the height: ";
		int h;
		std::cin >> h;
		initializeWindow();
		showSquare(w, h);
		break;
	case 2:
		std::cout << "Please enter the width: ";
		std::cin >> w;
		std::cout << "Please enter the height: ";
		std::cin >> h;
		std::cout << "Please enter the translation X offset (0 spawns the translated square ontop of the standard square, 200 can spawn off screen): ";
		int x;
		std::cin >> x;
		std::cout << "Please enter the translation Y offset (0 spawns the translated square ontop of the standard square, 200 can spawn off screen): ";
		int y;
		std::cin >> y;
		initializeWindow();
		showTranslatedSquare(w, h, x, y);
		break;
	case 3:
		std::cout << "Please enter the circle size (Over 225 will be cut off), allow time for the circle to draw: ";
		int size;
		std::cin >> size;
		initializeWindow();
		showCircle(size);
		break;
	case 4:
		std::cout << "Please enter the circle size (Over 225 will be cut off), allow time for the circle to draw: ";
		int fullSize;
		std::cin >> fullSize;
		initializeWindow();
		showFullCircle(fullSize);
		break;
	case 5:
		initializeWindow();
		showTriangle();
		break;
	case 6:
		int x0, y0, x1, y1;
		std::cout << "Enter the First Line X Coordinate: ";
		std::cin >> x0;
		std::cout << "Enter the First Line Y Coordinate: ";
		std::cin >> y0;
		std::cout << "Enter the Second Line X Coordinate: ";
		std::cin >> x1;
		std::cout << "Enter the Second Line Y Coordinate: ";
		std::cin >> y1;
		initializeWindow();
		showLine(x0, y0, x1, y1);
		break;
	case 7:
		std::cout << "Please enter the width: ";
		std::cin >> w;
		std::cout << "Please enter the height: ";
		std::cin >> h;
		std::cout << "Please enter the translation X offset (0 spawns the translated square ontop of the standard square, 200 can spawn off screen): ";
		std::cin >> x;
		std::cout << "Please enter the translation Y offset (0 spawns the translated square ontop of the standard square, 200 can spawn off screen): ";
		std::cin >> y;
		initializeWindow();
		showfake3D(w, h, x, y);
		break;
		break;
	default:
		std::cout << "Incorrect choice was made, please restart the program" << std::endl;
		break;
	}

	// Displays drawing to screen and holds until user closes window
	// You must call this after all your drawing calls
	// Program will exit after this line
	return MCG::ShowAndHold();

	// Advanced access - comment out the above DrawPixel and MCG::ShowAndHold lines, then uncomment the following:
	/* Variable to keep track of time
	float timer = 0.0f;

	 This is our game loop
	 It will run until the user presses 'escape' or closes the window
	while( MCG::ProcessFrame() )
	{
		Set every pixel to the same colour
		MCG::SetBackground( glm::ivec3( 0, 0, 0 ) );

		Change our pixel's X coordinate according to time
		pixelPosition.x = (windowSize.x / 2) + (int)(sin(timer) * 100.0f);
		Update our time variable
		timer += 1.0f / 60.0f;

		Draw the pixel to the screen
		MCG::DrawPixel( pixelPosition, pixelColour );

	}*/

	return 0;
}

void initializeWindow()
{
	// Variable for storing window dimensions
	glm::ivec2 windowSize(640, 480);

	// Call MCG::Init to initialise and create your window
	// Tell it what size you want the window to be
	if (!MCG::Init(windowSize))
	{
		// We must check if something went wrong
		// (this is very unlikely)
		std::cout << "Error" << std::endl;
	}

	// Sets every pixel to the same colour
	// parameters are RGBA, numbers are from 0 to 255
	MCG::SetBackground(glm::ivec3(255, 255, 255));

	// Preparing a position to draw a pixel
	//glm::ivec2 pixelPosition = windowSize / 2;


	// Preparing a colour to draw
	// Colours are RGB, each value ranges between 0 and 255
	glm::ivec3 color(0, 0, 255);
	glm::ivec3 color2(255, 0, 0);

	// Set center positions for x and y
	glm::vec2 centerX(windowSize.x / 2, 0);
	glm::vec2 centerY(0, windowSize.y / 2);
}

void showSquare(int width, int height)
{
	//Rectangle
	int sideLength = width;
	int length = height;


	glm::vec2 pixelPosition(centerX.x - (length / 2), centerY.y - (sideLength / 2));

	for (int i = 0; i < length; i++)
	{
		MCG::DrawPixel(pixelPosition, color);
		pixelPosition.x++;
	}
	for (int i = 0; i < sideLength; i++)
	{
		MCG::DrawPixel(pixelPosition, color);
		pixelPosition.y++;
	}
	for (int i = 0; i < length; i++)
	{
		MCG::DrawPixel(pixelPosition, color);
		pixelPosition.x--;
	}
	for (int i = 0; i < sideLength; i++)
	{
		MCG::DrawPixel(pixelPosition, color);
		pixelPosition.y--;
	}
}

void showTranslatedSquare(int width, int height, int xOffset, int yOffset)
{
	//Rectangle
	int sideLength = width;
	int length = height;


	glm::vec2 pixelPosition(centerX.x - (length / 2), centerY.y - (sideLength / 2));

	for (int i = 0; i < length; i++)
	{
		MCG::DrawPixel(pixelPosition, color);
		pixelPosition.x++;
	}
	for (int i = 0; i < sideLength; i++)
	{
		MCG::DrawPixel(pixelPosition, color);
		pixelPosition.y++;
	}
	for (int i = 0; i < length; i++)
	{
		MCG::DrawPixel(pixelPosition, color);
		pixelPosition.x--;
	}
	for (int i = 0; i < sideLength; i++)
	{
		MCG::DrawPixel(pixelPosition, color);
		pixelPosition.y--;
	}

	//translated
	glm::mat4 transMatrix = glm::translate(glm::mat4(), glm::vec3((xOffset), (yOffset), 0.0f));

	for (int i = 0; i < length; i++)
	{
		glm::vec4 Pos = transMatrix * glm::vec4(pixelPosition.x, pixelPosition.y, 0.0f, 1.0f);
		MCG::DrawPixel(Pos, color2);
		pixelPosition.x++;
	}
	for (int i = 0; i < sideLength; i++)
	{
		glm::vec4 Pos = transMatrix * glm::vec4(pixelPosition.x, pixelPosition.y, 0.0f, 1.0f);
		MCG::DrawPixel(Pos, color2);
		pixelPosition.y++;
	}
	for (int i = 0; i < length; i++)
	{
		glm::vec4 Pos = transMatrix * glm::vec4(pixelPosition.x, pixelPosition.y, 0.0f, 1.0f);
		MCG::DrawPixel(Pos, color2);
		pixelPosition.x--;
	}
	for (int i = 0; i < sideLength; i++)
	{
		glm::vec4 Pos = transMatrix * glm::vec4(pixelPosition.x, pixelPosition.y, 0.0f, 1.0f);
		MCG::DrawPixel(Pos, color2);
		pixelPosition.y--;
	}
}

void showCircle(int cSize)
{
	uint16_t circleSize = cSize;

	if (circleSize > 200)
	{
		circleSize = 200;
	}

	for (int i = 0; i < 50000; i++)
	{
		MCG::DrawPixel(glm::ivec2(centerX.x + circleSize * sin(i), centerY.y + circleSize * cos(i)), color);
	}
}

void showFullCircle(int fCSize)
{
	uint16_t fullCircleSize = fCSize;

	glm::ivec3 gradiant(0, 0, 255);

	if (fullCircleSize > 200)
	{
		fullCircleSize = 200;
	}
	while (fullCircleSize != 0)
	{
		for (int i = 0; i < 76000; i++)
		{
			MCG::DrawPixel(glm::ivec2(centerX.x + fullCircleSize * sin(i), centerY.y + fullCircleSize * cos(i)), gradiant);
		}
		gradiant.r++;
		fullCircleSize--;
	}
}

void showTriangle()
{
	uint16_t triangleSize = 300;
	glm::ivec2 pixelPosition(centerX.x - (triangleSize / 2), centerY.y + ((triangleSize / 2) / 2));
	glm::ivec2 origPoint = pixelPosition;

	for (int i = 0; i < triangleSize; i++) //Straight line
	{
		MCG::DrawPixel(pixelPosition, color);
		pixelPosition.x++;
	}
	for (int i = 0; i < triangleSize / 2; i++) //First angled line
	{
		MCG::DrawPixel(pixelPosition, color);
		pixelPosition--;
	}
	pixelPosition = origPoint;
	for (int i = 0; i < (triangleSize / 2) + 1; i++) // second angled line
	{
		MCG::DrawPixel(pixelPosition, color);
		pixelPosition.y--;
		pixelPosition.x++;
	}
}

void showLine(int x0, int y0, int x1, int y1)
{
	glm::vec2 pixelPosition(centerX.x, centerY.y);

	int dx = x1 - x0;
	int dy = y1 - y0;
	int d = 2 * dy - dx;
	int incrE = 2 * dy;
	int incrNE = 2 * (dy - dx);
	int x = x0;
	int y = y0;
	MCG::DrawPixel(glm::ivec2(x, y), color);

	while (x < x1)
	{
		if (d <= 0)
		{
			d += incrE;
			x++;
		}
		else
		{
			d += incrNE;
			x++;
			y++;
		}
		MCG::DrawPixel(glm::ivec2(x, y), color);
	}
}

void showfake3D(int width, int height, int xOffset, int yOffset)
{
	int sideLength = width;
	int length = height;


	glm::ivec2 pixelPosition(centerX.x - (length / 2), centerY.y - (sideLength / 2));

	glm::ivec2 firstPoint = pixelPosition;
	glm::ivec2 secondPoint;
	glm::ivec2 thirdPoint;
	glm::ivec2 fourthPoint;

	for (int i = 0; i < length; i++)
	{
		MCG::DrawPixel(pixelPosition, color);
		pixelPosition.x++;
	}

	secondPoint = pixelPosition;

	for (int i = 0; i < sideLength; i++)
	{
		MCG::DrawPixel(pixelPosition, color);
		pixelPosition.y++;
	}

	thirdPoint = pixelPosition;

	for (int i = 0; i < length; i++)
	{
		MCG::DrawPixel(pixelPosition, color);
		pixelPosition.x--;
	}

	fourthPoint = pixelPosition;

	for (int i = 0; i < sideLength; i++)
	{
		MCG::DrawPixel(pixelPosition, color);
		pixelPosition.y--;
	}

	//translated
	glm::mat4 transMatrix = glm::translate(glm::mat4(), glm::vec3((xOffset), (yOffset), 0.0f));

	glm::ivec4 Pos;

	bool line1 = false;
	bool line2 = false;
	bool line3 = false;
	bool line4 = false;

	for (int i = 0; i < length; i++)
	{
		Pos = transMatrix * glm::vec4(pixelPosition.x, pixelPosition.y, 0.0f, 1.0f);
		if (!line1)
		{
			showLine(firstPoint.x, firstPoint.y, Pos.x, Pos.y);
			line1 = true;
		}
		MCG::DrawPixel(Pos, color);
		pixelPosition.x++;
	}


	for (int i = 0; i < sideLength; i++)
	{
		Pos = transMatrix * glm::vec4(pixelPosition.x, pixelPosition.y, 0.0f, 1.0f);
		if (!line2)
		{
			showLine(secondPoint.x, secondPoint.y, Pos.x, Pos.y);
			line2 = true;
		}
		MCG::DrawPixel(Pos, color);
		pixelPosition.y++;
	}


	for (int i = 0; i < length; i++)
	{
		Pos = transMatrix * glm::vec4(pixelPosition.x, pixelPosition.y, 0.0f, 1.0f);
		if (!line3)
		{
			showLine(thirdPoint.x, thirdPoint.y, Pos.x, Pos.y);
			line3 = true;
		}
		MCG::DrawPixel(Pos, color);
		pixelPosition.x--;
	}


	for (int i = 0; i < sideLength; i++)
	{
		Pos = transMatrix * glm::vec4(pixelPosition.x, pixelPosition.y, 0.0f, 1.0f);
		if (!line4)
		{
			showLine(fourthPoint.x, fourthPoint.y, Pos.x, Pos.y);
			line4 = true;
		}
		MCG::DrawPixel(Pos, color);
		pixelPosition.y--;
	}


}