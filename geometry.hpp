/******************************************************************************
** File: geometry.hpp
** Project: Collada Export
** Author: Andrew Johnson
** Date Created: 12 July 2020
** Description: Stores the vertex and world information
******************************************************************************/


#ifndef GEOMETRY_HPP
#define GEOMETRY_HPP

class Geometry {
	private:
	double *pos;
	double angle;
	double pitch;
	double yaw;
	double *offset;
	int mouse_x;
	int mouse_y;
	bool* keyboard_state;
	bool* special_keyboard_state;
	
	public:
	Geometry();
	~Geometry();
	double* get_position()const;
	void set_position(double, double, double);
	double get_angle()const;
	void set_angle(double);
	double* get_offset()const;
	void set_offset(double, double, double);
	bool get_keyboard_state(int)const;
	void set_keyboard_state(int, bool);
	bool get_special_keyboard_state(int)const;
	void set_special_keyboard_state(int, bool);
	int get_mouse_x()const;
	int get_mouse_y()const;
	double get_pitch()const;
	void set_pitch(double);
	double get_yaw()const;
	void set_yaw(double);
	void adjust_view(int, int, int, int, double);
};

#endif
