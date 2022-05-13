#include <iostream>
#include "TSP.h"
using namespace std;


int main()
{
    setlocale(LC_ALL, "Russian");

    int num;

    cout << "Введите количесвто городов ";

    cin >> num;

    if (num > 2)
    {

        int equ = 0;

        int max_index = 0, work_index = 0;

        foo::TSP way(num, 0);

        way.reduction();
        way.min_way();
        way.fine();

        way.show_cal_map();

        foo::TSP way1(0, 999), way2(0, 999), sub_way1(0, 999), sub_way2(0, 999);

        way1.copy(way);
        way2.copy(way);

        way1.save_road();
        way1.matrix_reduction();
        way1.reduction();
        way1.min_way();

        way1.show_cal_map();

        way2.delete_road();
        way2.new_way();
        while (equ < num)
        {
            if (way1.get_min_way() < way2.get_min_way())
            {
                way1.fine();
                sub_way1.copy(way1);
                sub_way1.copy(way1);

                sub_way1.save_road();
                sub_way1.matrix_reduction();

                sub_way1.show_cal_map();

                sub_way1.reduction();
                sub_way1.min_way();

                way1.copy(sub_way1);

                sub_way2.delete_road();
                sub_way2.new_way();

                if (sub_way2.get_min_way() < way2.get_min_way())
                {
                    way2.copy(sub_way2);
                }
            }
            else
            {
                way2.reduction();
                way2.fine();
                sub_way1.copy(way2);
                sub_way2.copy(way2);

                way2.show_cal_map();

                sub_way1.save_road();
                sub_way1.matrix_reduction();
                sub_way1.reduction();
                sub_way1.min_way();



                if (sub_way1.get_min_way() < way1.get_min_way())
                {
                    way1.copy(sub_way1);
                }

                sub_way2.delete_road();
                sub_way2.new_way();

                way2.copy(sub_way2);
            }


            if (way1.get_min_way() < way2.get_min_way())
            {
                equ = way1.get_numr();
            }
            else
            {
                equ = way2.get_numr();
            }
        }

        if (way1.get_numr() == num)
        {
            way1.final_road();
            way1.save_road();

            cout << "Длинна минимального пути равна: " << way1.get_min_way() << endl;

            way1.show_roads();
        }
        if (way2.get_numr() == num)
        {
            way2.final_road();
            way2.save_road();

            cout << "Длинна минимального маршрута равна: " << way2.get_min_way() << endl;

            way2.show_roads();
        }
    }
    else
    {
        cout << "Введённое число городов не нуждается в вычислении" << endl;
    }

    return 0;
}
