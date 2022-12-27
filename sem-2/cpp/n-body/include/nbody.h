#include <cmath>
#include <fstream>
#include <iostream>
#include <map>
#include <memory>
#include <string_view>
#include <utility>
#include <vector>

struct Cartesian
{
    double x;
    double y;

    Cartesian(double x = 0, double y = 0);
    Cartesian operator+(const Cartesian & rhs) const;
    Cartesian operator-(const Cartesian & rhs) const;
    Cartesian operator*(double rhs) const;
    Cartesian operator/(double rhs) const;
    bool operator==(const Cartesian & rhs) const;
    bool operator!=(const Cartesian & rhs) const;
    friend std::ifstream & operator>>(std::ifstream & in, Cartesian & cartesian);
    friend std::ostream & operator<<(std::ostream & os, const Cartesian & cartesian);
};

class Quadrant
{
private:
    Cartesian center;
    double _length;

public:
    Quadrant(Cartesian center, double length);

    bool contains(Cartesian p) const;

    double length() const;

    Quadrant nw() const;
    Quadrant ne() const;
    Quadrant sw() const;
    Quadrant se() const;

    friend std::ostream & operator<<(std::ostream &, const Quadrant &);
};

const double Theta = 0.5;
const double G = 6.67e-11;

class Body
{
private:
    std::string name;
    double m;
    Cartesian position;
    Cartesian velocity;
    Cartesian acceleration = Cartesian(0, 0);
    Cartesian force = Cartesian(0, 0);

public:
    const std::string & getName() const;
    const Cartesian & getPosition() const;

    Body(Cartesian position = {0, 0}, Cartesian velocity = {0, 0}, double m = 0, const std::string & name = "");

    double distance(const Body & b) const;

    void add_force(const Body & b);

    void reset_force();

    void update(double delta_t);

    friend std::ostream & operator<<(std::ostream & out, const Body & b);

    bool in(Quadrant q) const;

    Body plus(const Body & b) const;
};

enum Condition
{
    Empty,
    Sheet,
    Inside
};

class BHTreeNode
{
private:
    Body body;
    Quadrant quadrant;
    Quadrant q_nw;
    Quadrant q_ne;
    Quadrant q_sw;
    Quadrant q_se;
    Condition condition;
    std::unique_ptr<BHTreeNode> nw;
    std::unique_ptr<BHTreeNode> ne;
    std::unique_ptr<BHTreeNode> sw;
    std::unique_ptr<BHTreeNode> se;

public:
    BHTreeNode(Quadrant quadrant);
    void insert(Body & b);

    const Body & getBody() const;
    const Quadrant & getQuadrant() const;
    Condition getCondition() const;
    const std::unique_ptr<BHTreeNode> & getNw() const;
    const std::unique_ptr<BHTreeNode> & getNe() const;
    const std::unique_ptr<BHTreeNode> & getSw() const;
    const std::unique_ptr<BHTreeNode> & getSe() const;
};

using Track = std::vector<Cartesian>;

class PositionTracker
{
protected:
    double size_universe;
    std::map<std::string, Body> data_start;
    std::map<std::string, Track> all_tracks;
    virtual void calculateF(Body & body) = 0;

public:
    PositionTracker(const std::string & filename);
    virtual Track track(const std::string & body_name, size_t end_time, size_t time_step) = 0;
    virtual ~PositionTracker() = default;
};

class BasicPositionTracker : public PositionTracker
{
protected:
    void calculateF(Body & body) override;

public:
    BasicPositionTracker(const std::string & filename);
    Track track(const std::string & body_name, size_t end_time, size_t time_step) override;
};

class FastPositionTracker : public PositionTracker
{
private:
    void calculateRecurF(Body & body, const std::unique_ptr<BHTreeNode> & u);

protected:
    std::unique_ptr<BHTreeNode> root{new BHTreeNode(Quadrant(Cartesian(size_universe / 2, size_universe / 2), size_universe / 2))};
    void calculateF(Body & body) override;

public:
    FastPositionTracker(const std::string & filename);
    Track track(const std::string & body_name, size_t end_time, size_t time_step) override;
};
