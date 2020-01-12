    1  sudo apt update
    2  sudo apt install htop
    3  htop
    4  python
    5  sudo apt install dirmngr
    6  sudo apt-key adv --keyserver hkp://keyserver.ubuntu.com:80 --recv E0C56BD4
    7  echo "deb http://repo.yandex.ru/clickhouse/deb/stable/ main/" | sudo tee /etc/apt/sources.list.d/clickhouse.list
    8  sudo apt update 
    9  sudo apt list --upgradable
   10  sudo apt update
   11  sudo apt upgrade
   12  sudo apt install -y clickhouse-server clickhouse-client
   13  sudo apt-get install dirmngr
   14  sudo apt-key adv --keyserver hkp://keyserver.ubuntu.com:80 --recv E0C56BD4
   15  echo "deb http://repo.yandex.ru/clickhouse/deb/stable/ main/" | sudo tee /etc/apt/sources.list.d/clickhouse.list
   16  sudo apt-get update
   17  sudo apt-get install -y clickhouse-server clickhouse-client
   18  echo "deb http://repo.yandex.ru/clickhouse/deb/stable/ main/" | sudo tee /etc/apt/sources.list.d/clickhouse.list
   19  sudo apt-key adv --keyserver hkp://keyserver.ubuntu.com:80 --recv E0C56BD4
   20  sudo apt update
   21  sudo apt -y install dirmngr clickhouse-server clickhouse-client
   22  curl -sSL https://get.docker.com | sh
   23  docker
   24  docker ps
   25  curl -fsSL https://get.docker.com -o get-docker.sh
   26  sh get-docker.sh 
   27  sudo usermod -aG docker $USER
   28  docker container run hello-world
   29  exit
   30  htop
   31  docker container run hello-world
   32  docker ps
   33  docker image
   34  docker ls
   35  docker image ls
   36  mkdir $HOME/some_clickhouse_database
   37  docker run -d --name some-clickhouse-server -p 8123:8123 -p 9000:9000 --ulimit nofile=262144:262144 --volume=$HOME/some_clickhouse_database:/var/lib/clickhouse yandex/clickhouse-server
   38  docker ps
   39  curl 'http://localhost:8123/'
   40  docker run -d --name some-clickhouse-server -p 8123:8123 -p 9000:9000 --ulimit nofile=262144:262144 --volume=$HOME/some_clickhouse_database:/var/lib/clickhouse yandex/clickhouse-server
   41  docker ls
   42  docker --help
   43  docker ps
   44  docker images
   45  curl 'http://localhost:8123/'
   46  curl 'http://0.0.0.0:8123/'
   47  docker run -d -p 8123:8123 -p 9000:9000 --ulimit nofile=262144:262144 --volume=$HOME/some_clickhouse_database:/var/lib/clickhouse yandex/clickhouse-server
   48  docker ps
   49  curl 'http://0.0.0.0:8123/'
   50  cat /proc/cpuinfo
   51  sudo apt-get install default-jre
   52  sudo mkdir /usr/share/elasticsearch
   53  cd /usr/share/elasticsearch
   54  wget https://packages.elastic.co/GPG-KEY-elasticsearch
   55  sudo wget https://packages.elastic.co/GPG-KEY-elasticsearch
   56  sudo apt-get install elasticsearch
   57  sudo nano /etc/elasticsearch/elasticsearch.yml
   58  sudo service elasticsearch restart
   59  curl 'http://0.0.0.0:9200/'
   60  curl 'http://localhost:9200/'
   61  curl 'http://localhost:9200'
   62  sudo nano /etc/elasticsearch/elasticsearch.yml
   63  sudo service elasticsearch restart
   64  reboot
   65  sudo reboot
   66  htop
   67  sudo service --help
   68  htop
   69  exit
   70  curl 'http://localhost:9200'
   71  ls
   72  pwd
   73  cd /home/
   74  ls
   75  cd pi/
   76  mkdir Downloads
   77  cd Downloads/
   78  wget https://artifacts.elastic.co/downloads/kibana/kibana-7.5.1-amd64.deb
   79  cd ..
   80  sudo mv ~/Downloads/kibana-7.5.1-amd64.deb /usr/share/kibana
   81  sudo dpkg -x kibana-5.4.2-i386.deb /usr/share/kibana
   82  cd /usr/share/kibana
   83  ls /usr/share/kibana 
   84  cd /usr/share/kibana
   85  mkdir /usr/share/kibana
   86  rm /usr/share/kibana
   87  sudo rm /usr/share/kibana
   88  mkdir /usr/share/kibana
   89  sudo mkdir /usr/share/kibana
   90  cd /usr/share/kibana
   91  wget https://artifacts.elastic.co/downloads/kibana/kibana-7.4.0-amd64.deb
   92  sudo wget https://artifacts.elastic.co/downloads/kibana/kibana-7.4.0-amd64.deb
   93  sudo dpkg -i --force-all kibana-7.4.0-amd64.deb
   94  sudo nano /etc/kibana/kibana.yml 
   95  sudo service kibana start
   96  ls
   97  ls /etc/init.d/
   98  sudo service --status-all
   99  sudo service elasticsearch status
  100  sudo service kibana status
  101  sudo service --help
  102  sudo service --full-restart
  103  sudo reboot
  104  exit
  105  htop
  106  cd /tmp/
  107  sudo curl -L "https://github.com/docker/compose/releases/download/1.25.0/docker-compose-$(uname -s)-$(uname -m)" -o /usr/local/bin/docker-compose
  108  sudo chmod +x /usr/local/bin/docker-compose
  109  docker-compose --version
  110  ls
  111  sudo curl -L "https://github.com/docker/compose/releases/download/1.25.0/docker-compose-$(uname -s)-$(uname -m)" -o /usr/local/bin/docker-compose
  112  docker --version
  113  cd
  114  pwd
  115  sudo curl -L "https://github.com/docker/compose/releases/download/1.25.0/docker-compose-$(uname -s)-$(uname -m)" -o /usr/local/bin/docker-compose
  116  ls
  117  ping google.com
  118  pip
  119  sudo apt install crul
  120  sudo apt install curl
  121  sudo curl -L "https://github.com/docker/compose/releases/download/1.25.0/docker-compose-$(uname -s)-$(uname -m)" -o /usr/local/bin/docker-composecurl -L https://github.com/docker/compose/releases/download/1.25.1/docker-compose-`uname -s`-`uname -m` -o /usr/local/bin/docker-compose
  122  ls
  123  ls -lh
  124  sudo wget "https://github.com/docker/compose/releases/download/1.25.0/docker-compose-$(uname -s)-$(uname -m)" -o /usr/local/bin/docker-composecurl -L https://github.com/docker/compose/releases/download/1.25.1/docker-compose-`uname -s`-`uname -m` -o /usr/local/bin/docker-compose
  125  ls
  126  ls /usr/local/bin/docker-compose
  127  docker-compose
  128  docker-compose --version
  129  sudo curl -L "https://github.com/docker/compose/releases/download/1.25.0/docker-compose-$(uname -s)-$(uname -m)" -o /usr/local/bin/docker-composecurl -L https://github.com/docker/compose/releases/download/1.25.1/docker-compose-`uname -s`-`uname -m` -o /usr/local/bin/docker-compose
  130  docker-compose --version
  131  sudo curl -L https://raw.githubusercontent.com/docker/compose/$(docker-compose version --short)/contrib/completion/bash/docker-compose -o /etc/bash_completion.d/docker-compose
  132  sudo sudo curl -L https://raw.githubusercontent.com/docker/compose/$(docker-compose version --short)/contrib/completion/bash/docker-compose -o /etc/bash_completion.d/docker-compose
  133  curl https://bootstrap.pypa.io/get-pip.py -o get-pip.py && sudo python3 get-pip.py
  134  sudo curl https://bootstrap.pypa.io/get-pip.py -o get-pip.py && sudo python3 get-pip.py
  135  pip
  136  sudo apt update
  137  sudo apt-get install python-setuptools python-dev build-essential 
  138  sudo easy_install pip 
  139  pip
  140  sudo reboot
  141  pip
  142  sudo easy_install pip 
  143  sudo apt upbgrade
  144  sudo apt upgrade
  145  sudo apt-get install python-setuptools python-dev build-essential 
  146  easy_install
  147  sudo apt-get install python-pip python-dev build-essential 
  148  sudo pip install --upgrade pip 
  149  sudo pip install --upgrade virtualenv 
  150  pip
  151  sudo pip3 install docker-compose
  152  python3
  153  curl https://bootstrap.pypa.io/get-pip.py -o get-pip.py && sudo python3 get-pip.py
  154  pip
  155  pip -v
  156  sudo pip install docker-compose
  157  sudo apt-get install libffi-dev libssl-dev
  158  sudo pip3 install docker-compose
  159  sudo apt-get install libffi-dev libssl-dev
  160  sudo apt install python3-dev
  161  sudo apt install git
  162  git clone git@github.com:BenWhiteJam/elasticRaspAdruino.git
  163  git clone https://github.com/BenWhiteJam/elasticRaspAdruino.git
  164  ls
  165  sudo apt-get install -y python3 python3-pip
  166  sudo pip3 install docker-compose
  167  docker-compose -v
  168  cd elasticRaspAdruino/
  169  history > setup.sh
  170  cat setup.sh 
  171  git status
  172  git add .
  173  git commit -m "init setup of raspb 3 clickhouse docker docker-compose elk"
  174  git push
  175  git config --global user.email "benjamin.weiss.hm@googlemail.com"
  176  git config --global user.name "BenWhiteJam"
  177  git status
  178  git push
  179  ssh-keygen -t rsa -b 4096 -C "benjamin.weiss.hm@googlemail.com"
  180  cat /home/pi/.ssh/id_rsa.pub 
  181  git push
  182  mc
  183  cd ..
  184  rm -r elasticRaspAdruino/
  185  sudo rm -r elasticRaspAdruino/
  186  git clone git@github.com:BenWhiteJam/elasticRaspAdruino.git
  187  cd elasticRaspAdruino/
  188  history > setup.sh
