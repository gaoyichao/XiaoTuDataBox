#ifndef __ARRAY2D_HPP__
#define __ARRAY2D_HPP__

#include <iostream>
#include <cassert>

template <class T>
class Array2D {
    public:
        Array2D() : array(NULL), rows(0), cols(0) {}
        Array2D(int r, int c) : array(NULL), rows(0), cols(0) { resize(r, c); }
        Array2D(int r, int c, T const & v) : array(NULL), rows(0), cols(0)
        {
            resize(r, c);
            int n = r * c;
            for (int i = 0; i < n; i++)
                array[i] = v;
        }

        ~Array2D()
        {
            if (NULL != array)
                delete [] array;
        }

        void resize(int r, int c, T const & v)
        {
            resize(r, c);
            int n = r * c;
            for (int i = 0; i < n; i++)
                array[i] = v;
        }
        void resize(int r, int c)
        {
            if (r == rows && c == cols)
                return;

            int n = r * c;
            T * arr = NULL;
            if (n > 0)
                arr = new T[n];


            if (NULL != array) {
                int rr = (r < rows) ? r : rows;
                int cc = (c < cols) ? c : cols;

                for (int i = 0; i < rr; i++)
                for (int j = 0; j < cc; j++)
                    arr[i * cols + j] = array[i * cols + j];

                delete [] array;
            }

            array = arr;
            rows = r;
            cols = c;
        }

        T & at(int n)
        {
            assert(n < (rows * cols));
            return array[n];
        }

        T & at(int r, int c)
        {
            if (r > rows || c > cols) {
                int rr = (r > rows) ? r : rows;
                int cc = (c > cols) ? c : cols;
                resize(rr, cc);
            }

            return array[r * cols + c];
        }

        T const & at(int n) const
        {
            assert(n < (rows * cols));
            return array[n];
        }

        T const & at(int r, int c) const
        {
            assert(r < rows);
            assert(c < cols);

            return array[r * cols + c];
        }

        T & operator () (int n) { return at(n); }
        T & operator () (int r, int c) { return at(r, c); }
        T const & operator () (int n) const { return at(n); }
        T const & operator () (int r, int c) const { return at(r, c); }

        friend std::ostream & operator << (std::ostream & stream, Array2D const & array) {
            int r, c;
            array.size(r, c);

            if (r <= 0 || c <= 0)
                return stream;

            r = r - 1;
            for (int i = 0; i < r; i++) {
                stream << "| " << array(i, 0);
                for (int j = 1; j < c; j++)
                    stream << "\t" << array(i, j);
                stream << " |" << std::endl;
            }

            stream << "| " << array(r, 0);
            for (int j = 1; j < c; j++)
                stream << "\t" << array(r, j);
            stream << " |";

            return stream;
        }

        bool insert_row(int r, int n, T const & v)
        {
            if (!insert_row(r, n))
                return false;

            for (int i = r; i < (r+n); i++)
                for (int j = 0; j < cols; j++)
                    array[i * cols + j] = v;

            return true;
        }

        /*
         * insert_row - 在@r行插入@n行
         */
        bool insert_row(int r, int n)
        {
            if (r > rows)
                return false;

            int nrows = rows + n;
            int nsize = nrows * cols;
            T * arr = new T[nsize];

            for (int i = 0; i < r; i++)
                for (int j = 0; j < cols; j++)
                    arr[i * cols + j] = array[i * cols + j];

            for (int i = (r+n); i < nrows; i++)
                for (int j = 0; j < cols; j++)
                    arr[i * cols + j] = array[(i-n) * cols + j];

            delete [] array;
            array = arr;
            rows = nrows;
            return true;
        }

        bool insert_column(int c, int n, T const & v)
        {
            if (!insert_column(c, n))
                return false;

            for (int i = 0; i < rows; i++)
                for (int j = c; j < (c+n); j++)
                    array[i * cols + j] = v;

            return true;
        }
        /*
         * insert_column - 在@c列插入@n列
         */
        bool insert_column(int c, int n)
        {
            if (c > cols)
                return false;

            int ncols = cols + n;
            int nsize = rows * ncols;
            T * arr = new T[nsize];

            for (int j = 0; j < c; j++)
                for (int i = 0; i < rows; i++)
                    arr[i * ncols + j] = array[i * cols + j];

            for (int j = (c+n); j < ncols; j++)
                for (int i = 0; i < rows; i++)
                    arr[i * ncols + j] = array[i * cols + j - n];

            delete [] array;
            array = arr;
            cols = ncols;
            return true;
        }

        bool remove_row(int r, int n)
        {
            if ((r + n - 1) >= rows || 0 == n || 0 == rows || 0 == cols)
                return false;

            int nrows = rows - n;
            T * arr = NULL;
            if (nrows > 0) {
                int nsize = nrows * cols;
                arr = new T[nsize];

                for (int i = 0; i < r; i++)
                    for (int j = 0; j < cols; j++)
                        arr[i * cols + j] = array[i * cols + j];

                for (int i = r; i < nrows; i++)
                    for (int j = 0; j < cols; j++)
                        arr[i * cols + j] = array[(i + n) * cols + j];
            }

            delete [] array;
            array = arr;
            rows = nrows;

            return true;
        }

        bool remove_column(int c, int n)
        {
            if ((c + n - 1) >= cols || 0 == n || 0 == rows || 0 == cols)
                return false;

            int ncols = cols - n;
            T * arr = NULL;
            if (ncols > 0) {
                int nsize = rows * ncols;
                arr = new T[nsize];

                for (int j = 0; j < c; j++)
                    for (int i = 0; i < rows; i++)
                        arr[i * ncols + j] = array[i * cols + j];

                for (int j = c; j < ncols; j++)
                    for (int i = 0; i < rows; i++)
                        arr[i * ncols + j] = array[i * cols + j + n];
            }

            delete [] array;
            array = arr;
            cols = ncols;

            return true;
        }

        bool swap_row(int r1, int r2)
        {
            if (r1 >= rows || r2 >= rows)
                return false;

            if(r1 == r2)
                return true;

            for (int j = 0; j < cols; j++) {
                T tmp = array[r1 * cols + j];
                array[r1 * cols + j] = array[r2 * cols + j];
                array[r2 * cols + j] = tmp;
            }

            return true;
        }

        bool swap_column(int c1, int c2)
        {
            if (c1 >= cols || c2 >= cols)
                return false;

            if(c1 == c2)
                return true;

            for (int i = 0; i < rows; i++) {
                T tmp = array[i * cols + c1];
                array[i * cols + c1] = array[i * cols + c2];
                array[i * cols + c2] = tmp;
            }

            return true;
        }


        int num_rows() const { return rows; }
        int num_cols() const { return cols; }
        int size() const { return rows * cols; }
        int size(int & r, int & c) const
        {
            r = rows;
            c = cols;
            return r * c;
        }
    private:
        T *array;
        int rows;
        int cols;
};

#endif


