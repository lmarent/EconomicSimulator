#!/usr/bin/env bash

# Script to install Economic Simulator

# Author: Thiago Teixeira
# University of Massachusetts Amherst

eval cd $HOME
eval mkdir economicSimulator && cd ./economicSimulator

echo "Installing Economic Simulator ..."
git clone https://github.com/lmarent/network_agents_ver2.git

echo "Installing dependencies ..."
echo "This might take a while!"
sleep 3
sudo apt-get update
sudo apt-get -y install openssl libssl-dev
sudo apt-get -y install libiodbc2 libiodbc2-dev
sudo apt-get -y install mysql-client
sudo apt-get -y install libmysqlclient-dev
sudo apt-get -y install pkg-config
sudo apt-get -y install cmake   

POCO_VERSION=1.8.0
wget http://pocoproject.org/releases/poco-$POCO_VERSION/poco-$POCO_VERSION-all.tar.gz 
make --version
tar -xzvf poco-$POCO_VERSION-all.tar.gz
rm poco-$POCO_VERSION-all.tar.gz
eval cd poco-$POCO_VERSION-all 
cmake -DENABLE_DATA_MYSQL=ON
./configure        
make -s
sudo make -s install
export LD_LIBRARY_PATH="/usr/local/lib:$LD_LIBRARY_PATH"
sleep 3

eval cd ../network_agents_ver2/foundation/
libtoolize
aclocal
autoheader
autoconf
automake --add-missing
./configure
make
make install
sleep 3

eval cd ../CostFunctions/
libtoolize
aclocal
autoheader
autoconf
automake --add-missing
./configure
make
sudo make install
sleep 3

eval cd ../MarketPlaceServer/
libtoolize
aclocal
autoheader
autoconf
automake --add-missing
./configure
make
sudo make install
sleep 3

eval cd ../ClockServer/
libtoolize
aclocal
autoheader
autoconf
automake --add-missing
./configure
make
sudo make install
sleep 3
