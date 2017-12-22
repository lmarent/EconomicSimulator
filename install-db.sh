#!/usr/bin/env bash

# Script to install Economic Simulator

# Author: Thiago Teixeira
# University of Massachusetts Amherst

eval cd $HOME
eval mkdir economicSimulator && cd ./economicSimulator

sudo apt-get -y install mysql-server
sudo netstat -tap | grep mysqlb         
pip install django
