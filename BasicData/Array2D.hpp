#ifndef __ARRAY2D_HPP__
#define __ARRAY2D_HPP__

#include <iostream>
#include <cassert>

template <int rows, int cols, class T>
class Array2D {
    public:
        Array2D() {}
 
        T & operator () (int i) { return array[i]; }
        T & operator () (int r, int c) { return array[r * cols + c]; }

        T const & operator () (int i) const { return array[i]; }
        T const & operator () (int r, int c) const { return array[r * cols + c]; }

        friend std::ostream & operator << (std::ostream & stream, Array2D const & array) {
            stream << "| " << array(0, 0);
            for (int j = 1; j < cols; j++)
                stream << "\t" << array(0, j);
            stream << " |" << std::endl;

            int r = rows - 1;
            for (int i = 1; i < r; i++) {
                stream << "| " << array(i, 0);
                for (int j = 1; j < cols; j++)
                    stream << "\t" << array(i, j);
                stream << " |" << std::endl;
            }

            stream << "| " << array(r, 0);
            for (int j = 1; j < cols; j++)
                stream << "\t" << array(r, j);
            stream << " |";

            return stream;
        }



        int r() const { return rows; }
        int c() const { return cols; } 
        int n() const { return rows * cols; }
    private:
        T array[rows * cols];
};

#endif

