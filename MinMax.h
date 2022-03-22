/******************************************************
   This file is part of the BioData project
   (c) 2018 Erin Gee   http://www.eringee.net

   This file normalizes values using their minimum and maximum values.

   Contributing authors:
   (c) 2018 Erin Gee
   (c) 2018 Sofian Audry
   (c) 2017 Thomas Ouellet Fredericks
   (c) 2017 Martin Peach

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.

******************************************************/

#ifndef MIN_MAX_H_
#define MIN_MAX_H_

#include <algorithm>

class MinMax {
    float _input;
    float _min;
    float _max;
    float _value;
    bool _firstPass;

  public:
    MinMax() {
      reset();
    }

    void reset() {
      _input = _min = _max = _value = 0;
      _firstPass = true;
    }

    void adapt(float lop) {
      lop = std::min(std::max(lop, 0.f), 1.f);
      lop = lop * lop;

      _min += (_input - _min) * lop;
      _max += (_input - _max) * lop;
    }
    
    float filter(float f) {

      _input = f;

      if ( _firstPass ) {
        _firstPass = false;
        _min = f;
        _max = f;
      } else {
        if ( f > _max ) _max = f;
        if ( f < _min ) _min = f;
      }

      if ( _max == _min ) {
        _value = 0.5;
      } else {
        _value = (f - _min) / ( _max - _min);
      }

      return _value;
    }

    float getMax() {
      return _max;
    }

    float getMin() {
      return _min;
    }


};

#endif
