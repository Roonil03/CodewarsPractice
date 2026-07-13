#include <sstream>
#include <cmath>
#include <cctype>
#include <regex>
#include <cmath>
#include <tuple>
#include <map>
#include <stack>
#include <iostream>

using namespace std;

template <typename T>
struct coord
{
    using value_type = T;
    value_type row, col;

    constexpr coord() : row(value_type()), col(value_type()) {}
    constexpr coord(const value_type& _row, const value_type& _col) : row(_row), col(_col) {}
    constexpr coord(initializer_list<value_type> li) : row(*li.begin()), col(*(li.begin() + 1)) {}

    bool operator==(const coord& val) const { return row == val.row && col == val.col; }
    coord operator+(const coord& val) const { return { row + val.row, col + val.col }; }
    coord operator-(const coord& val) const { return { row - val.row, col - val.col }; }
    coord& operator+=(const coord& val) { return *this = operator+(val); }
    coord& operator-=(const coord& val) { return *this = operator-(val); }
};

class Train;
class TrackIterator;
class Track
{
public:
    using iterator = TrackIterator;
    using position = coord<ptrdiff_t>;
    using line = string;
    using value_type = typename line::value_type;
private:
    static const value_type blank = ' ';
public:
    static const value_type station = 'S';
    static const position left;
    static const position right;
    static const position top;
    static const position bottom;
public:
    Track(const string& str) {
        istringstream is(str);
        string s;
        while (getline(is, s)) { track.push_back(s); }
        left_top = { 0, static_cast<ptrdiff_t>(track.front().find_first_not_of(' ')) };
    }
    iterator begin();
    iterator rbegin();
    position next_position(const position& cur, const position& pre) const;
    value_type& at(position& pos) { return const_cast<value_type&>(at(const_cast<const position&>(pos))); }
    const value_type& at(const position& pos) const { return track.at(pos.row).at(pos.col); }
    void print(int step, const Train& ta, const Train& tb, const Track::iterator& pa, const Track::iterator& pb) const;
    bool valid_position(const position& pos) const {
        if (pos.row < 0 || pos.row >= track.size()) { return false; }
        if (pos.col < 0 || pos.col >= track.at(pos.row).size()) { return false; }
        return true;
    }
private:
    bool check_hori(const position& pos) const { return valid_position(pos) && (at(pos) == '-' || at(pos) == '+' || at(pos) == station); }
    bool check_vert(const position& pos) const { return valid_position(pos) && (at(pos) == '|' || at(pos) == '+' || at(pos) == station); }
    bool check_slas(const position& pos) const { return valid_position(pos) && (at(pos) == '/' || at(pos) == 'X' || at(pos) == station); }
    bool check_bksl(const position& pos) const { return valid_position(pos) && (at(pos) == '\\' || at(pos) == 'X' || at(pos) == station); }
private:
    vector<string> track;
    position left_top;
};
const Track::position Track::left{ 0, -1 };
const Track::position Track::right{ 0, 1 };
const Track::position Track::top{ -1, 0 };
const Track::position Track::bottom{ 1, 0 };

class TrackIterator
{
    using difference_type = ptrdiff_t;
public:
    TrackIterator(Track& _track, const Track::position& _cur, const Track::position& _next, const Track::position& _pre)
        : track(_track), cur(_cur), next(_next), pre(_pre) {}
    TrackIterator operator+(difference_type diff) const {
        TrackIterator tmp = *this;
        for (; diff != 0; --diff) { ++tmp; }
        return tmp;
    }
    TrackIterator operator-(difference_type diff) const {
        TrackIterator tmp = *this;
        for (; diff != 0; --diff) { --tmp; }
        return tmp;
    }
    TrackIterator& operator++() {
        auto&& tmp = track.next_position(next, cur);
        pre = cur; cur = next; next = tmp;
        return *this;
    }
    TrackIterator& operator--() {
        auto&& tmp = track.next_position(pre, cur);
        next = cur; cur = pre; pre = tmp;
        return *this;
    }
    bool operator==(const TrackIterator& val) const {
        return cur == val.cur && next == val.next && pre == val.pre;
    }
    bool operator!=(const TrackIterator& val) const { return !operator==(val); }
    Track::value_type& operator*() { return track.at(cur); }
    Track::position value() const { return cur; }
    void reverse() {
        auto tmp = next;
        next = pre;
        pre = tmp; }
private:
    Track& track;
    Track::position cur, next, pre;

    friend void Track::print(int step, const Train& ta, const Train& tb, const Track::iterator& pa, const Track::iterator& pb) const;
};

class Train
{
public:
    static const char express_name = 'x';
public:
    string name;
    size_t length;
    bool express;
    bool clockwise;
public:
    Train(const string& str)
        : name(str), length(str.size()), express(tolower(str.front()) == express_name), pause_time(0), clockwise(str.back() >= 'A' && str.back() <= 'Z') {}
    void run_cycle(Track::iterator& pos) {
        if (express) { ++pos; return; }
        if (pause_time != 0) {
            --pause_time;
            if (pause_time == 0) { ++pos; }
            return;
        }
        if (*pos == Track::station) { pause_time = length - 1; return; }
        ++pos;
    }
private:
    int pause_time;

    friend int train_crash(const string& track_str, const string& a_train_str, int a_train_pos, const string& b_train_str, int b_train_pos, int limit);
};

inline Track::iterator Track::begin()
{
    position&& r0 = left_top + right;
    position&& r1 = left_top + bottom;
    if (!check_vert(r1)) { r1 += left; }
    return iterator(*this, left_top, r0, r1);
}

inline Track::iterator Track::rbegin()
{
    position&& r0 = left_top + right;
    position&& r1 = left_top + bottom;
    if (at(r1) == blank) { r1 += left; }
    return iterator(*this, left_top, r1, r0);
}

Track::position Track::next_position(const position& cur, const position& pre) const {
    const auto& land = at(cur);
    const auto&& dir = cur - pre;

    if (land == '|' || land == '-' || land == '+' || land == 'X' || land == 'S') { return cur + dir; }
    if (land == '/') {
        if (check_hori(cur + left) && (dir == bottom || dir == bottom + left)) { return cur + left; }
        if (check_hori(cur + right) && (dir == top || dir == top + right)) { return cur + right; }
        if (check_vert(cur + top) && (dir == right || dir == top + right)) { return cur + top; }
        if (check_vert(cur + bottom) && (dir == left || dir == bottom + left)) { return cur + bottom; }
        if (check_slas(cur + top + right) && (dir == right || dir == top || dir == top + right)) { return cur + top + right; }
        if (check_slas(cur + bottom + left) && (dir == left || dir == bottom || dir == bottom + left)) { return cur + bottom + left; }
    }
    else if (land == '\\') {
        if (check_hori(cur + left) && (dir == top || dir == top + left)) { return cur + left; }
        if (check_hori(cur + right) && (dir == bottom || dir == bottom + right)) { return cur + right; }
        if (check_vert(cur + top) && (dir == left || dir == top + left)) { return cur + top; }
        if (check_vert(cur + bottom) && (dir == right || dir == bottom + right)) { return cur + bottom; }
        if (check_bksl(cur + top + left) && (dir == left || dir == top || dir == top + left)) { return cur + top + left; }
        if (check_bksl(cur + bottom + right) && (dir == right || dir == bottom || dir == bottom + right)) { return cur + bottom + right; }
    }
    return position();
}

template <typename T>
bool in_range(T beg, const T& end, const T& val)
{
    for (; beg != end; ++beg) {
        if (beg.value() == val.value()) { return true; }
    }
    return false;
}

void Track::print(int step, const Train& ta, const Train& tb, const Track::iterator& pa, const Track::iterator& pb) const
{
    cout << "step = " << step << endl;
    for (size_t r = 0; r < track.size(); ++r) {
        for (size_t c = 0; c < track.at(r).size(); ++c) {
            Track::position pos(r, c);
            bool flag = false;
            if (pos == pa.cur) { cout << (char)toupper(ta.name.front()); continue; }
            if (pos == pb.cur) { cout << (char)toupper(tb.name.front()); continue; }
            for (auto it = pa - ta.length + 1; it != pa + 1; ++it) {
                if (pos == it.cur) {
                    cout << (char)tolower(ta.name.front());
                    flag = true;
                    break;
                }
            }
            if (flag) { continue; }
            for (auto it = pb - tb.length + 1; it != pb + 1; ++it) {
                if (pos == it.cur) {
                    cout << (char)tolower(tb.name.front());
                    flag = true;
                    break;
                }
            }
            if (flag) { continue; }
            cout << at(pos);
        }
        cout << endl;
    }
    cout << endl;
//     system("pause");
}

int train_crash(const string& track_str, const string& a_train_str, int a_train_pos, const string& b_train_str, int b_train_pos, int limit)
{
    cout << track_str << endl;
    cout << a_train_str << endl;
    cout << a_train_pos << endl;
    cout << b_train_str << endl;
    cout << b_train_pos << endl;
    cout << limit << endl;

    Track track(track_str);
    Train a_train(a_train_str), b_train(b_train_str);

    auto&& beg = track.begin();
    auto&& a = beg + a_train_pos;
    //auto a = beg;
    auto&& b = beg + b_train_pos;
    //for (int i = 0; i < a_train_pos; ++i, ++a) {
    //    track.print(i, a_train, b_train, a, beg);
    //}
    if (!a_train.clockwise) { a.reverse(); }
    if (!b_train.clockwise) { b.reverse(); }
    for (auto it = a - a_train.length + 1; it != a; ++it) {
        if (in_range(it + 1, a + 1, it)) { return 0; }
        if (in_range(b - b_train.length + 1, b + 1, it)) { return 0; }
    }
    for (auto it = b - b_train.length + 1; it != b; ++it) {
        if (in_range(it + 1, b + 1, it)) { return 0; }
    }
    
    if (*a == Track::station) { a_train.pause_time = 1; }
    if (*b == Track::station) { b_train.pause_time = 1; }
    for (int step = 0; step <= limit; ++step) {
        if(step>=1912)track.print(step, a_train, b_train, a, b);
        if (in_range(a - a_train.length + 1, a, a) ||
            in_range(a - a_train.length + 1, a + 1, b) ||
            in_range(b - b_train.length + 1, b + 1, a) ||
            in_range(b - b_train.length + 1, b, b))
        { return step; }
        a_train.run_cycle(a);
        b_train.run_cycle(b);
    }
    return -1;
}

// Solution referenced from https://www.codewars.com/users/luoxinjie1146 and https://www.codewars.com/users/pruebiwis