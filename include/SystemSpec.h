#ifndef SYSTEMSPEC_H

#define SYSTEMSPEC_H

/* 
* A solar system where a single star is in a fixed position and the planets only interact with the it not each other
* Use units of m for distance and Kg for mass
* Everything is in 2 dimensions

Probably move the definitions to a separate cpp file soon ish
*/

#include <iostream>
#include <string_view>
#include <string>

class Position
{
private:
    double m_x;
    double m_y;

public:
    Position() = default;
    Position(double x, double y) : m_x{x}, m_y{y} {}

    friend std::ostream &operator<<(std::ostream &out, const Position &pos)
    {
        out << '(' << pos.m_x << ", " << pos.m_y << ')';
        return out;
    }
};

class Velocity
{
private:
    double m_x;
    double m_y;

public:
    Velocity() = default;
    Velocity(double x, double y) : m_x{x}, m_y{y} {}

    friend std::ostream &operator<<(std::ostream &out, const Velocity &vel)
    {
        out << '(' << vel.m_x << ", " << vel.m_y << ')';
        return out;
    }
};

class AstrObject
{
    // Abstract base class for an astronomical object (AO)
protected:
    std::string m_name;
    double m_mass;
    double m_radius;
    Position m_pos;
    Velocity m_vel;

    // Also protect this constructor so this class can't be directly instantiated
    AstrObject(std::string name, double mass, double radius, Position pos, Velocity vel)
        : m_name{name}, m_mass{mass}, m_radius{radius}, m_pos{pos}, m_vel{vel} {}

public:
    virtual std::string getType() const = 0;
    const Position &getPos() const { return m_pos; }
    const Velocity &getVel() const { return m_vel; }
    const double &getMass() const { return m_mass; }

    friend std::ostream &operator<<(std::ostream &out, const AstrObject &astr)
    {
        // An overloaded output operator that works on all derived classes
        // Displays the type of astronomical object, its name, position and velocity.
        out << "[" << astr.getType() << "] " << astr.m_name << ": Mass(" << astr.getMass() << ")";
        out << " Pos[m]" << astr.getPos() << " Vel[m/s]" << astr.getVel() << "\n";
        return out;
    }
};

class Star : public AstrObject
{
    // All stars have velocity (0,0).
public:
    Star(std::string name, double mass, double radius, Position pos)
        : AstrObject(name, mass, radius, pos, Velocity(0, 0)) {}

    virtual std::string getType() const override
    { // Type of AO
        return std::string("Star");
    }
};

class Planet : public AstrObject
{
public:
    Planet(std::string name, double mass, double radius, Position pos, Velocity vel)
        : AstrObject(name, mass, radius, pos, vel) {}
    virtual std::string getType() const override
    { // Type of AO
        return std::string("Planet");
    }
};

#endif