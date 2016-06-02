# Script used to install all the dependencies

sudo apt-get update

mkdir -p bin
cd bin
wget 'https://googletest.googlecode.com/files/gtest-1.7.0.zip'
unzip gtest-1.7.0.zip
rm gtest-1.7.0.zip
ln -s ../bin/gtest-1.7.0/ ../gumbo-parser/gtest
sudo pip install BeautifulSoup
sudo pip install html5lib==0.95

# Making sure libtoolize is installed
sudo apt-get install libcunit1-dev automake autotools-dev build-essential libtool

cd ../gumbo-parser/
./autogen.sh
./configure
make
sudo make install
sudo python setup.py sdist install

# Making sure lib icu is intalled
sudo apt-get install libicu-dev
