from __future__ import division
from foundation.Message import Message
from foundation.Bid import Bid
from foundation.Agent import Agent
from foundation.Service import Service
from foundation.DecisionVariable import DecisionVariable
from ProviderAgentException import ProviderException
from foundation.FoundationException import FoundationException
from foundation.AgentServer import AgentServerHandler
from foundation.AgentType import AgentType

import foundation.agent_properties
import uuid
import logging
import logging.handlers
import time
import xml.dom.minidom
from math import fabs
import os
import threading


LOG_FILENAME = 'customer.log'
# Check if log exists and should therefore be rolled
needRoll = os.path.isfile(LOG_FILENAME)

logger = logging.getLogger('consumer_application')

fh = logging.handlers.RotatingFileHandler(LOG_FILENAME, backupCount=5)
fh.setLevel(logging.INFO)
formatter = logging.Formatter('%(threadName)-10s) - (asctime)s - %(name)s - %(levelname)s - %(message)s')
fh.setFormatter(formatter)
logger.addHandler(fh)

# This is a stale log, so roll it
if needRoll:
	# Roll over on application start
    logger.handlers[0].doRollover()



class ConsumerStatic(Consumer):
    ''' 
    The Consumer class defines methods to be used by the consumer
    agent to purchase offers on the marketplace, initizalize the
    agent, get the disutility function, and execute the buying
    algorithm. 
    '''

    
    def __init__(self, strID, Id, serviceId, customer_seed):
        try:
            
            super(Consumer, self).__init__(strID, Id, agent_type, serviceId, customer_seed)
            
            logger.debug('Agent: %s - Consumer Created', self._list_vars['strId'])
        except FoundationException as e:
            raise ProviderException(e.__str__())

	'''
	The run method activates the avaiable consumer agents.
	'''
    def run(self):
        proc_name = self.name
        self.start_agent()
        self.initialize()
        while (True):
            if (self._list_vars['State'] == AgentServerHandler.TERMINATE):
                break
            else:
                if (self._list_vars['State'] == AgentServerHandler.TO_BE_ACTIVED):
                    logger.debug('Agent: %s - Initialized' , self._list_vars['strId'])
                    self._list_vars['State'] = AgentServerHandler.ACTIVATE
                    logger.debug('Agent: %s - Now in state %s' , self._list_vars['strId'], self._list_vars['State'])
                    self.exec_algorithm()
                    self.printDecisionVariables()
                    self.lock.acquire()
                    try:
                        self._list_vars['State'] = AgentServerHandler.IDLE
                    finally:
                        self.lock.release() 
                elif (self._list_vars['State'] == AgentServerHandler.IDLE):
                    time.sleep(0.1)
        # logger.debug('Agent: %s - Shuting down', self._list_vars['strId'])
        # Close the sockets
        self.stop_agent()
        return
		

# End of Provider class
