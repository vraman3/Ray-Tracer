#pragma once

//Author: Vishwanath Raman
class ColourClass
{
private:
	double red, green, blue;

public:
	ColourClass();
	ColourClass(double, double, double);

	double GetRed();
	double GetGreen();
	double GetBlue();

	void SetRed(double);
	void SetGreen(double);
	void SetBlue(double);

	ColourClass operator*(const double) const;
	ColourClass operator/(const double) const;
	ColourClass operator+(const double) const;
	ColourClass operator-(const double) const;
	ColourClass operator*(const ColourClass&) const;
	ColourClass operator+(const ColourClass&) const;
	ColourClass operator-(const ColourClass&) const;

	void resetColour();
};

