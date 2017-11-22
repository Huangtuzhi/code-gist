#!/bin/bash

rm entrance
g++ entrance.cpp base_module.cpp ./business_logic/business_a.cpp ./business_logic/business_b.cpp -o entrance
