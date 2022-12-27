#include "nbody.h"

Cartesian::Cartesian(double x, double y)
    : x(x)
    , y(y)
{
}
Cartesian Cartesian::operator+(const Cartesian & rhs) const
{
    return {x + rhs.x, y + rhs.y};
}
Cartesian Cartesian::operator-(const Cartesian & rhs) const
{
    return {x - rhs.x, y - rhs.y};
}

Cartesian Cartesian::operator*(const double rhs) const
{
    return {x * rhs, y * rhs};
}

Cartesian Cartesian::operator/(const double rhs) const
{
    return {x / rhs, y / rhs};
}

bool Cartesian::operator==(const Cartesian & rhs) const
{
    return x == rhs.x &&
            y == rhs.y;
}

bool Cartesian::operator!=(const Cartesian & rhs) const
{
    return !(rhs == *this);
}

std::ifstream & operator>>(std::ifstream & in, Cartesian & cartesian)
{
    in >> cartesian.x >> cartesian.y;
    return in;
}

std::ostream & operator<<(std::ostream & os, const Cartesian & cartesian)
{
    os << "x: " << cartesian.x << " y: " << cartesian.y;
    return os;
}

Body::Body(Cartesian position, Cartesian velocity, const double m, const std::string & name)
    : name(name)
    , m(m)
    , position(position)
    , velocity(velocity)
{
}

double Body::distance(const Body & b) const
{
    const Cartesian d = position - b.position;
    return std::sqrt(d.x * d.x + d.y * d.y);
}

void Body::add_force(const Body & b)
{
    const double r = distance(b);
    const double F = G * m / r * b.m / r;
    force = force + (b.position - position) * F / r;
}

void Body::reset_force()
{
    force = {0, 0};
}

void Body::update(const double delta_t)
{
    acceleration = force / m;
    velocity = velocity + acceleration * delta_t;
    position = position + velocity * delta_t;
}

std::ostream & operator<<(std::ostream & out, const Body & b)
{
    out << "name: " << b.name << "\n";
    out << "position:\n"
        << b.position << "\n";
    out << "velocity:\n"
        << b.velocity << "\n";
    out << "acceleration:\n"
        << b.acceleration << "\n";
    out << "force:\n"
        << b.force << "\n";
    out << "mass: " << b.m << "\n";
    return out;
}

Body Body::plus(const Body & b) const
{
    const double new_mass = m + b.m;
    const Cartesian new_position = (position * m + b.position * b.m) / new_mass;
    const Cartesian new_velocity = (velocity * m + b.velocity * b.m) / new_mass;
    return {new_position, new_velocity, new_mass, name + b.name};
}

bool Body::in(const Quadrant q) const
{
    return q.contains(position);
}

const std::string & Body::getName() const
{
    return name;
}

const Cartesian & Body::getPosition() const
{
    return position;
}

Quadrant::Quadrant(Cartesian center, double length)
    : center(center)
    , _length(length)
{
}

bool Quadrant::contains(Cartesian p) const
{
    return (center.x - _length <= p.x && p.x <= center.x + _length && center.y - _length <= p.y && p.y <= center.y + _length);
}

double Quadrant::length() const
{
    return _length;
}

Quadrant Quadrant::nw() const
{
    return Quadrant(Cartesian(center.x - _length / 2, center.y + _length / 2), _length / 2);
}

Quadrant Quadrant::ne() const
{
    return Quadrant(Cartesian(center.x + _length / 2, center.y + _length / 2), _length / 2);
}

Quadrant Quadrant::sw() const
{
    return Quadrant(Cartesian(center.x - _length / 2, center.y - _length / 2), _length / 2);
}

Quadrant Quadrant::se() const
{
    return Quadrant(Cartesian(center.x + _length / 2, center.y - _length / 2), _length / 2);
}

std::ostream & operator<<(std::ostream & out, const Quadrant & q)
{
    out << "length: " << q.length() << "\n";
    out << "center:\n"
        << q.center << "\n";
    return out;
}

BHTreeNode::BHTreeNode(Quadrant quadrant)
    : body()
    , quadrant(quadrant)
    , q_nw(quadrant.nw())
    , q_ne(quadrant.ne())
    , q_sw(quadrant.sw())
    , q_se(quadrant.se())
    , condition(Empty)
{
}

void BHTreeNode::insert(Body & b)
{
    bool was = false;
    auto checkChildren = [&](Body & _b, Quadrant & q, std::unique_ptr<BHTreeNode> & u) {
        if (!was && _b.in(q)) {
            if (!u) {
                u = std::unique_ptr<BHTreeNode>{new BHTreeNode(q)};
            }
            u->insert(_b);
            was = true;
        }
    };

    if (condition == Empty) {
        body = b;
        condition = Sheet;
        return;
    }
    else if (condition == Sheet) {
        checkChildren(body, q_nw, nw);
        checkChildren(body, q_sw, sw);
        checkChildren(body, q_ne, ne);
        checkChildren(body, q_se, se);
        was = false;
        condition = Inside;
    }
    checkChildren(b, q_nw, nw);
    checkChildren(b, q_sw, sw);
    checkChildren(b, q_ne, ne);
    checkChildren(b, q_se, se);
}
const Body & BHTreeNode::getBody() const
{
    return body;
}
const Quadrant & BHTreeNode::getQuadrant() const
{
    return quadrant;
}
Condition BHTreeNode::getCondition() const
{
    return condition;
}
const std::unique_ptr<BHTreeNode> & BHTreeNode::getNw() const
{
    return nw;
}
const std::unique_ptr<BHTreeNode> & BHTreeNode::getNe() const
{
    return ne;
}
const std::unique_ptr<BHTreeNode> & BHTreeNode::getSw() const
{
    return sw;
}
const std::unique_ptr<BHTreeNode> & BHTreeNode::getSe() const
{
    return se;
}

PositionTracker::PositionTracker(const std::string & filename)
{
    std::ifstream in(filename);
    in >> size_universe;
    while (!in.eof()) {
        std::string name;
        Cartesian pos, vel;
        double m;
        in >> pos >> vel >> m >> name;
        if (name.empty()) {
            break;
        }
        data_start[name] = Body(pos, vel, m, name);
        all_tracks[name] = Track({pos});
    }
}

Track PositionTracker::track(const std::string & body_name, size_t end_time, size_t time_step)
{
    for (size_t i = 0; i < end_time; i++) {
        for (auto & body : data_start) {
            calculateF(body.second);
        }
        for (auto & body : data_start) {
            body.second.update(time_step);
            all_tracks[body.first].push_back(body.second.getPosition());
            body.second.reset_force();
        }
    }
    return all_tracks[body_name];
}

BasicPositionTracker::BasicPositionTracker(const std::string & filename)
    : PositionTracker(filename)
{
}

Track BasicPositionTracker::track(const std::string & body_name, size_t end_time, size_t time_step)
{
    return PositionTracker::track(body_name, end_time, time_step);
}

FastPositionTracker::FastPositionTracker(const std::string & filename)
    : PositionTracker(filename)
{
    for (auto & body : data_start) {
        root->insert(body.second);
    }
}

Track FastPositionTracker::track(const std::string & body_name, size_t end_time, size_t time_step)
{
    return PositionTracker::track(body_name, end_time, time_step);
}

void BasicPositionTracker::calculateF(Body & body)
{
    for (const auto & b : data_start) {
        if (body.getName() != b.first) {
            body.add_force(b.second);
        }
    }
}

void FastPositionTracker::calculateF(Body & body)
{
    calculateRecurF(body, root);
}

void FastPositionTracker::calculateRecurF(Body & body, const std::unique_ptr<BHTreeNode> & u)
{
    if (!u) {
        return;
    }
    if (u->getCondition() == Sheet && u->getBody().getName() != body.getName()) {
        body.add_force(u->getBody());
    }
    else if (u->getCondition() == Inside) {
        if (2 * u->getQuadrant().length() < Theta * body.distance(u->getBody())) {
            body.add_force(u->getBody());
        }
        else {
            calculateRecurF(body, u->getSe());
            calculateRecurF(body, u->getSw());
            calculateRecurF(body, u->getNe());
            calculateRecurF(body, u->getNw());
        }
    }
}