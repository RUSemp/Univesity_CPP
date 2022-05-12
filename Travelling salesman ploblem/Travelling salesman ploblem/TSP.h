#pragma once
#include <iostream>
namespace foo {
	class TSP
	{
    private:
        int** _ways = NULL;
        int** _cal_map = NULL;
        int** _roads;
        int _num = 0, _maxf = 0, _rowf = 0, _colf = 0, _numr = 0, _min_way = 999, _inc_way = 0;
    public:

        TSP( int num, int min_way);
        ~TSP();
        void reduction();
        void fine();
        void save_road();
        void delete_road();
        void min_way();
        void new_way();
        void matrix_reduction();
        void final_road();
        void copy(TSP ways);
        int** get_ways();
        int get_numr();
        int get_inc_way();
        int get_min_way();
        int** get_cal_map();
        void show_roads();
        void show_ways();
        void show_cal_map();
    };

}
