# Economic Simulator

## Instructions for installation on [GENI Testbed](http://www.geni.net/)
1. Create a slice and reserve resources using an existing RSpec
    Follow these instructions:
    http://groups.geni.net/geni/wiki/HowTo/LoadAnExistingRSpec
    
    In the Choose Rspec field, drop-down menu, select the following RSpec:
    ![SelectRSpec](SelectingCustomRSpec.png)
    

    The nodes login information should be the following:
    * users
        ```
       host info: ssh <username>@pc2.instageni.northwestern.edu -p <port>
        ip: 10.10.1.1
        ```

    * users-mkt
        ```
        host info: ssh <username>@pc2.instageni.northwestern.edu -p <port>
         ip: 10.10.1.2
            10.10.2.1
            10.10.6.2
       ```

    * users-providers
        ```
        host info: ssh <username>@pc2.instageni.northwestern.edu -p <port>
        ip: 10.10.2.2
            10.10.3.2
         ```

    * transit-mkt
       ```
        host info: ssh <username>@pc2.instageni.northwestern.edu -p <port>
        ip: 10.10.3.1
            10.10.4.2
            10.10.5.2
        ```

    * transit-providers
        ```
        host info: ssh <username>@pc2.instageni.northwestern.edu -p <port>
       ip: 10.10.4.1
        ```

    * database
        ```
        host info: ssh \<username\>@pc2.instageni.northwestern.edu -p <port>
        ip: 10.10.5.1
            10.10.6.1
        ```
	
2. Install the codebase on the nodes
    * On the nodes `user-mkt`, `transit-mkt`, and `database`:  
        ```
        $ cd /home/
        $ git clone https://github.com/lmarent/network_agents_ver2.git
        $ wget http://pocoproject.org/releases/poco-1.7.5/poco-1.7.5-all.tar.gz        
        $ sudo apt-get -y install openssl libssl-dev
        $ sudo apt-get -y install libiodbc2 libiodbc2-dev
        $ sudo apt-get -y install mysql-client
        $ sudo apt-get install pkg-config
        
        $ make --version
        $ tar -xzvf poco-X.Y.tar
        $ cd poco-X.Y
        $ sudo apt-get -y install cmake        
        $ cmake -DENABLE_DATA_MYSQL=ON
        $ ./configure        
        $ make -s
        $ sudo make -s install
        $ export LD_LIBRARY_PATH="/usr/local/lib:$LD_LIBRARY_PATH"
        
        $ cd ../network_agents_ver2/foundation/
        $ libtoolize
        $ aclocal
        $ autoheader
        $ autoconf
        $ automake --add-missing
        $ ./configure
        $ make
        $ make install
        
        $ cd ../network_agents_ver2/CostFunctions/
        $ libtoolize
        $ aclocal
        $ autoheader
        $ autoconf
        $ automake --add-missing
        $ ./configure
        $ make
        $ sudo make install
        
        $ cd ../network_agents_ver2/MarketPlaceServer/
        $ libtoolize
        $ aclocal
        $ autoheader
        $ autoconf
        $ automake --add-missing
        $ ./configure
        $ make
        $ sudo make install
        
        $ cd ../network_agents_ver2/ClockServer/
        $ libtoolize
        $ aclocal
        $ autoheader
        $ autoconf
        $ automake --add-missing
        $ ./configure
        $ make
        $ sudo make install
        ```

    * On the nodes `users`, `transit-providers`, `user-providers`, and `database`:    
        ```
        $ cd /home/
        $ git clone https://github.com/lmarent/network_agents_ver2_python.git
        $ sudo apt-get install python-mysqldb  
        $ sudo apt-get install python-numpy
        $ sudo apt-get install python-scipy      
        ```

    * On the `database` node:    
        ```
        $ sudo apt-get -y install mysql-server
        $ sudo netstat -tap | grep mysqlb 
        $ sudo apt-get install python-numpy
        $ sudo apt-get install python-scipy        
        $ sudo apt-get install python-mysqldb
        
        $ sudo apt-get install python-pip
        $ pip install django
        ```
        
    * On the `database` node: Setup the database    
        ```
        usr=admin
        pwd=password
        CREATE DATABASE `Network_Simulation` /*!40100 DEFAULT CHARACTER SET latin1 */;
        
        Data base Configuration

        1. Configure mysql server to accept connections from remote nodes by copying the file my.cfg into /etc/mysql
        2. Connect to the database using the sql admin user that you create during installation. For example, execute:

            mysql -h 127.0.0.1 -P 3306 -u root -p

        3. Create the database by executing in mysql
        CREATE DATABASE Network_Simulation;

        4. Create the admin user. This user is the owner of the database.

          GRANT ALL ON *.* to admin@localhost IDENTIFIED BY 'password'; 
          GRANT ALL ON *.* to admin@'%' IDENTIFIED BY 'password'; 

        5. Import dump files: 

	   5.1 download the file: Dump20161201.zip located in the root of the github project. The dump files were created using the export functionality of mysql workbench.
	   5.2 uncompress the file
	   5.3 import the file using the data import functionality of mysql workbench.
        ```

3. Configure properties files on nodes

    * On the `database` node: Setup the database    
        ```
        Modify the file ClockServer.properties
        
        cd /home/lamarent/network_agents_ver2/ClockServer/src
        nano ClockServer.properties
        
        The file should be configured in the following way
        \# --------------------------------
        \# ClockServer properties file
        \# --------------------------------
        
        listening_port=3333
        name=Clock_Server
        
        \# every interval is 4 Seconds
        time_intervals=4000
        
        \# a cycle is the time required for purchasing in the whole network of providers.
        intervals_per_cycle=2
        interval_for_customer_activation = 0
        bid_periods=7
        
        \# database configuration
        db_host=10.10.6.1
        db_port=3306
        db_user=admin
        db_password=password
        db_name=Network_Simulation
        
        \# If not specified it adds demand/ as the subdirectory ( it must finish with /).
        demand_directory=demand/
        ```
    
    * On the `transit-marketplace` node:    
        ```
        Modify the file MarketPlaceServer.properties
        
        cd /home/lamarent/network_agents_ver2/MarketPlaceServer/src
        nano MarketPlaceServer.properties
        
        \# --------------------------------
        \# MarkePlaceServer properties file
        \# --------------------------------
        
        \# --------------  1. Clock Server related    -------------
        
        clock_server_address=10.10.5.1
        clock_port=3333
        
        \# --------------  2. Market Place Server related    -------------
        name=Market_backhaul
        listening_port=5555
        type=market_place
        
        intervals_per_cycle=2
        send_information_on_interval=0
        
        \#-----------------3. Database related information  ----------------
        db_host=10.10.5.1
        db_port=3306
        db_user=admin
        db_password=password
        db_name=Network_Simulation
        
        pareto_fronts_to_send=2
        ```

    * On the `user-marketplace` node:    
        ```
        Modify the file MarketPlaceServer.properties
        
        cd /home/lamarent/network_agents_ver2/MarketPlaceServer/src
        nano MarketPlaceServer.properties
        
        \# --------------------------------
        \# MarkePlaceServer properties file
        \# --------------------------------
        
        \# --------------  1. Clock Server related    -------------
        
        clock_server_address=10.10.6.1
        clock_port=3333
        
        \# --------------  2. Market Place Server related    -------------
        name=Market_Isp
        listening_port=5555
        type=market_place
        
        intervals_per_cycle=2
        send_information_on_interval=1
        
        \#-----------------3. Database related information  ----------------
        db_host=10.10.6.1
        db_port=3306
        db_user=admin
        db_password=password
        db_name=Network_Simulation
        
        pareto_fronts_to_send=2
        ```

    * On the `transit-providers` node:    
        ```
        Modify the file agent_properties.py
        
        cd /home/lamarent/network_agents_ver2_python/agents/foundation
        nano agent_properties.py
        
        '''
        This file defines the agent_properties.
        '''
        \# ClockServer listening port and Marketplace listening port are
        \# defined below.
        clock_listening_port = 3333
        mkt_place_listening_port = 5555
        
        \# The listening ports for presenter, provider, and consumer are 
        \# defined below.
        l_port_presenter = 12000
        l_port_provider = 13000
        l_port_consumer = 14000
        
        \# Address for the database server information
        addr_database = '10.10.6.1'
        port_database = 3306
        user_database = 'admin'
        user_password = 'password'
        database_name = 'Network_Simulation'
        
        \# Addresses for marketplace, clockserver, and own agent address
        \# are defined below.
        addr_mktplace_isp = '10.10.2.1'
        addr_mktplace_backhaul = '10.10.3.1'
        addr_clock_server = '10.10.6.1'
        addr_agent_mktplace_isp = '10.10.4.1'
        addr_agent_mktplace_backhaul = '10.10.4.1'
        addr_agent_clock_server = '10.10.4.1'
        
        threshold = 2
        own_neighbor_radius = 0.05
        others_neighbor_radius = 100 # almost every bid is in the neighbor.
        initial_number_bids = 5
        num_periods_market_share = 3
        intervals_per_cycle = 2
        \# This variable establishes the provider types that can be executed.
        provider_types = 'Provider'

        \# directory results
        result_directory = 'results/'
        ```

    * On the `users-providers` node:    
        ```
        Modify the file agent_properties.py
        
        cd /home/lamarent/network_agents_ver2_python/agents/foundation
        nano agent_properties.py
        
        The file should be as the following
        
        '''
        This file defines the agent_properties.
        '''
        \# ClockServer listening port and Marketplace listening port are
        \# defined below.
        clock_listening_port = 3333
        mkt_place_listening_port = 5555
        
        \# The listening ports for presenter, provider, and consumer are 
        \# defined below.
        l_port_presenter = 12000
        l_port_provider = 13000
        l_port_consumer = 14000
        
        \# Address for the database server information
        addr_database = '10.10.6.1'
        port_database = 3306
        user_database = 'admin'
        user_password = 'password'
        database_name = 'Network_Simulation'
        
        \# Addresses for marketplace, clockserver, and own agent address
        \# are defined below.
        addr_mktplace_isp = '10.10.2.1'
        addr_mktplace_backhaul = '10.10.3.1'
        addr_clock_server = '10.10.6.1'
        addr_agent_mktplace_isp = '10.10.2.2'
        addr_agent_mktplace_backhaul = '10.10.3.2'
        addr_agent_clock_server = '10.10.3.2'
        
        threshold = 2
        own_neighbor_radius = 0.05
        others_neighbor_radius = 100 # almost every bid is in the neighbor.
        initial_number_bids = 5
        num_periods_market_share = 3
        intervals_per_cycle = 2
        provider_types = 'ProviderEdge,ProviderEdgeMonopoly'
        
        \# directory results
        result_directory = 'results/'        
        ```

    * On the `users` node:    
        ```
        Modify the file agent_properties.py
        
        cd /home/lamarent/network_agents_ver2_python/agents/foundation
        nano agent_properties.py
        
        '''
        This file defines the agent_properties.
        '''
        \# ClockServer listening port and Marketplace listening port are
        \# defined below.
        clock_listening_port = 3333
        mkt_place_listening_port = 5555
        
        \# The listening ports for presenter, provider, and consumer are 
        \# defined below.
        l_port_presenter = 12000
        l_port_provider = 13000
        l_port_consumer = 14000
        
        \# Address for the database server information
        addr_database = '10.10.6.1'
        port_database = 3306
        user_database = 'admin'
        user_password = 'password'
        database_name = 'Network_Simulation'
        
        \# Addresses for marketplace, clockserver, and own agent address
        \# are defined below.
        addr_mktplace_isp = '10.10.1.2'
        addr_mktplace_backhaul = '10.10.3.1'
        addr_clock_server = '10.10.5.1'
        addr_agent_mktplace_isp = '10.10.1.1'
        addr_agent_mktplace_backhaul = '10.10.1.1'
        addr_agent_clock_server = '10.10.1.1'
        
        threshold = 2
        own_neighbor_radius = 0.05
        others_neighbor_radius = 100 # almost every bid is in the neighbor.
        initial_number_bids = 5
        num_periods_market_share = 3
        intervals_per_cycle = 2
        
        \# directory results
        result_directory = 'results/'
        ```
        
4. Running the code
    Run the following agents (in order):

    1. On the `Database` VM: 
        ```
        $ sudo /etc/init.d/mysql start
        $ cd /home/network_agents_ver2/ClockServer/src
        $ ./ClockServer
        ```
    
    2. On the `Transit Marketplace` VM:
        ```
        $ cd /home/network_agents_ver2/MarketPlaceServer/src
        $ ./MarketPlaceServer
        ```
    
    3. On the `Users Marketplace` VM:
        ```
        $ cd /home/network_agents_ver2/MarketPlaceServer/src
        $ ./MarketPlaceServer
        ```
    
    4. On the `Transit Provider` VM:
        ```
        $ cd /home/network_agents_ver2_python/agents
        $ python Provider.py
        ```    
    
    5. On the `User Provider` VM:
        ```
        $ cd /home/network_agents_ver2_python/agents
        $ python ProviderEdge.py
        ```
    
    6. On the `Users` VM:
        ```
        $ cd /home/network_agents_ver2_python/agents
        $ python Consumers.py
        ```
