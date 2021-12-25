#include "Scheme.hpp"

int Scheme::get_index_by_id(int id) const {
    for (int i = 0; i < sz; i++)
        if (figures_[i]->get_id() == id)
            return i;
    return -1;
}

Figure* Scheme::find_figure_by_id(int id) const {
    int ind = get_index_by_id(id);
    return ((ind == -1) ? nullptr : figures_[ind]);
}

Scheme::Scheme(int capacity) {
    figures_ = new Figure*[capacity];
}

Scheme::~Scheme() {
    for(int i = 0; i < sz; i++)
    	delete figures_[i];
    delete[] figures_;
}

void Scheme::push_back_figure(Figure *fg) {
    figures_[sz++] = fg;
}

void Scheme::remove_figure(int id) {
    int ind = get_index_by_id(id);
    delete figures_[ind];
    figures_[ind] = nullptr;
    for (int i = ind + 1; i < sz; i++)
        figures_[i - 1] = figures_[i];
    figures_[--sz] = nullptr;
}

void Scheme::print_all_figures() {
    for (int i = 0; i < sz; i++)
        figures_[i]->print();
}

void Scheme::zoom_figure(int id, int factor) {
    find_figure_by_id(id)->zoom(factor);
}

Figure *Scheme::is_inside_figure(int x, int y) {
    for (int i = 0; i < sz; i++)
        if (figures_[i]->is_inside(x, y))
            return figures_[i];
    return nullptr;
}

void Scheme::move(int id, int new_x, int new_y) {
    find_figure_by_id(id)->move(new_x, new_y);
}
