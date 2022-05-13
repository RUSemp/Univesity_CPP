#include "TSP.h"


namespace foo {

    TSP::TSP( int num, int min_way)
    {
        _ways = new int* [num + 1];
        _cal_map = new int* [num + 1];
        for (int count = 0; count < num + 1; count++)
        {
            _cal_map[count] = new int[num + 1];
            _ways[count] = new int[num + 1];
        }

        for (int row = 0; row < num; row++)
        {
            for (int col = 0; col < num; col++)
            {
                if (row == col)
                {
                    _cal_map[row][col] = 999;
                    _ways[row][col] = 999;
                    std::cout << _ways[row][col] << " ";
                    continue;
                }

                _ways[row][col] = rand() % 10;
                _cal_map[row][col] = _ways[row][col];
                std::cout << _ways[row][col] << " ";
            }
            std::cout << std::endl;
        }

        _cal_map[num][num] = 999;
        _ways[num][num] = 999;

        _num = num; // число "городов"
        _roads = new int* [num+1];//здесь храним пути
        for (int count = 0; count < num+1; count++)
        {
            _roads[count] = new int[2];
            _roads[count][0] = 0;
            _roads[count][1] = 0;
        }

        _min_way = min_way;
    }

    TSP::~TSP()
    {

    }

    void TSP::reduction()
    {

        for (int row = 0; row < _num; row++)
        {
            _cal_map[row][_num] = 999; //Ставим большое число, чтоб в дальнейшем сравнивать с остальными элементами таблицы
            for (int column = 0; column < _num; column++)
            {
                if (_cal_map[row][column] == 999)
                {
                    continue;
                }
                if (_cal_map[row][column] < _cal_map[row][_num]) //находим минимум строки
                {
                    _cal_map[row][_num] = _cal_map[row][column];
                }
            }

            for (int column = 0; column < _num; column++) //редукция строк
            {
                if (_cal_map[row][column] == 999)
                {
                    continue;
                }
                _cal_map[row][column] -= _cal_map[row][_num];
            }
        }

        for (int col = 0; col < _num; col++)
        {
            _cal_map[_num][col] = 999; //Ставим большое число, чтоб в дальнейшем сравнивать с остальными элементами таблицы
            for (int row = 0; row < _num; row++)
            {
                if (_cal_map[row][col] == 999)
                {
                    continue;
                }

                if (_cal_map[row][col] < _cal_map[_num][col]) //ищем минимум столбца
                {
                    _cal_map[_num][col] = _cal_map[row][col];
                }
            }

            for (int row = 0; row < _num; row++) // редукция столбцов
            {
                if (_cal_map[row][col] == 999)
                {
                    continue;
                }
                _cal_map[row][col] -= _cal_map[_num][col];
            }
        }
    }

    void TSP::fine()
    {
        _maxf = 0;
        int rmin = 999, cmin = 999;

        for (int row = 0; row < _num; row++)
        {
            for (int col = 0; col < _num; col++)
            {
                if (_cal_map[row][col] == 999)
                {
                    continue;
                }
                if (_cal_map[row][col] == 0) // находим нули и считаем штраф для каждого
                {
                    for (int count = 0; count < _num; count++)
                    {
                        if ((_cal_map[row][count] < rmin) && (count != col))
                        {
                            rmin = _cal_map[row][count];
                        }
                        if ((_cal_map[count][col] < cmin) && (count != row))
                        {
                            cmin = _cal_map[count][col];
                        }
                    }

                    if ((_maxf < cmin + rmin) || (_maxf == cmin + rmin)) //нам понядобятся только ячейка с максимальным штрафом,
                    {						 //если штрафы равны, берём любую нулевую ячейку
                        _maxf = cmin + rmin;
                        _colf = col;
                        _rowf = row;
                    }
                }
            }
        }
    }

    void TSP::save_road()
    {
        _roads[_numr][0] = _rowf;
        _roads[_numr][1] = _colf;

        std::cout << "Сохранена дорога: " << _roads[_numr][0] << "---->" << _roads[_numr][1] << std::endl;
        std::cout << "Длинна: " << _ways[_roads[_numr][0]][_roads[_numr][1]] << std::endl;
        std::cout << std::endl;

        _numr++;
    }

    void TSP::delete_road()
    {
        _cal_map[_rowf][_colf] = 999;
    }

    void TSP::min_way()
    {
        for (int count = 0; count < _num; count++)
        {
            if ((_cal_map[count][_num] == 999) || (_cal_map[_num][count] == 999))
            {
                continue;
            }
            _min_way += _cal_map[count][_num] + _cal_map[_num][count];
        }
    }

    void TSP::matrix_reduction()
    {       
        for (int count = 0; count < _num; count++)
        {
            _cal_map[count][_colf] = 999;
            _cal_map[_rowf][count] = 999;
        }
        _cal_map[_colf][_rowf] = 999;

        _inc_way = 1;
    }

    void TSP::final_road()
    {
        for (int row = 0; row < _num; row++)
        {
            for (int col = 0; col < _num; col++)
            {
                if (_cal_map[row][col] != 999)
                {
                    _rowf = row;
                    _colf = col;

                }
            }
        }
    }

    void TSP::copy(TSP ways)
    {
        _ways = ways._ways;
        
        _cal_map = new int* [ways._num + 1];
        for (int row = 0; row < ways._num + 1; row++)
        {
            _cal_map[row] = new int[ways._num + 1];

            for (int col = 0; col < ways._num + 1; col++)
            {
                _cal_map[row][col] = ways._cal_map[row][col];
            }
        }

        _roads = new int* [ways._num + 1];
        for (int count = 0; count < ways._num + 1; count++)
        {
            _roads[count] = new int[2];

            _roads[count][0] = ways._roads[count][0];
            _roads[count][1] = ways._roads[count][1];
        }

        _num = ways._num;
        _maxf = ways._maxf;
        _rowf = ways._rowf;
        _colf = ways._colf;
        _numr = ways._numr;
        _min_way = ways._min_way;
    }

    void TSP::new_way()
    {
        _min_way += _maxf;
    }

    int** TSP::get_ways()
    {
        return _ways;
    }

    int TSP::get_numr()
    {
        return _numr;
    }

    int TSP::get_inc_way()
    {
        return _inc_way;
    }

    int TSP::get_min_way()
    {
        return _min_way;
    }

    int** TSP::get_cal_map()
    {
        return _cal_map;
    }

    void TSP::show_roads()
    {
        for (int count = 0; count < _num; count++)
        {
            std::cout << _roads[count][0] << "-->" << _roads[count][1] << " Длинна: " << _ways[_roads[count][0]][_roads[count][1]] << std::endl;
        }
    }

    void TSP::show_ways()
    {
        std::cout << "show_ways()" << std::endl;
        for (int row = 0; row < _num + 1; row++)
        {
            for (int column = 0; column < _num + 1; column++)
            {
                std::cout << _ways[row][column] << " ";
            }
            std::cout << std::endl;
        }
    }

    void TSP::show_cal_map()
    {
        std::cout << "show_cal_map()" << std::endl;
        for (int row = 0; row < _num + 1; row++)
        {
            for (int column = 0; column < _num + 1; column++)
            {
                std::cout.width(4);
                std::cout << _cal_map[row][column];
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }
}
