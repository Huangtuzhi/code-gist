#!/usr/bin/python
# -*- coding:utf-8 -*-

import logging
import logging.handlers

class LogRecorder(object):
    def __init__(self, format, log_file, name):
        self._log_format = format
        self._log_file = log_file
        self._log_name = name
        self._log_level = logging.DEBUG

        handler = logging.handlers.RotatingFileHandler(
            self._log_file,
            maxBytes = 1048576 * 2, # 2MB
            backupCount = 5,
            )
        handler.setFormatter(logging.Formatter(self._log_format))
        self._logger = logging.getLogger(self._log_name)
        self._logger.addHandler(handler)
        self._logger.setLevel(self._log_level)

    def log(self, content):
        self._logger.info(content)

if __name__=='__main__':
    FORMAT = '%(asctime)s - %(name)s - %(message)s'
    LOG_FILE = "/tmp/log.tmp"
    logger = LogRecorder(FORMAT, LOG_FILE, "EmojiPaserLog")
    logger.log("log system is ok")
