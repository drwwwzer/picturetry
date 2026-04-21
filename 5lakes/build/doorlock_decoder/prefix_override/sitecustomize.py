import sys
if sys.prefix == '/usr':
    sys.real_prefix = sys.prefix
    sys.prefix = sys.exec_prefix = '/home/drwwwzer/many/RM_myself/5lakes/install/doorlock_decoder'
