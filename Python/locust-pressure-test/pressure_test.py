#!/usr/bin/env python
# -*- coding=utf-8 -*-

from locust import HttpLocust,TaskSet,task
 
class testBroadBand(TaskSet):
    # task装饰该方法为一个事务方法的参数用于指定该行为的执行权重。参数越大，每次被虚拟用户执行概率越高，不设置默认是1，
    header = {"User-Agent": "Mozilla/5.0 "
                "(Windows NT 6.1; Win64; x64) AppleWebKit/537.36 "
                "(KHTML, like Gecko) Chrome/60.0.3112.101 Safari/537.36"}

    # 测试 case 1
    @task()
    def test1(self):
        req_data = '''post json'''
        r = self.client.post("xxx1", data=req_data)
        print "retcode: " + str(r.status_code)
        print "content: " + r.text
        assert r.status_code == 200

    # 测试 case 2
    @task()
    def test2(self):
        req_data = '''post json2'''
        r = self.client.post("xxx2", data=req_data)
        print "retcode: " + str(r.status_code)
        print "content: " + r.text
        assert r.status_code == 200

    # 测试 case 3
    @task()
    def test3(self):
        req_data = '''post json3'''
        r = self.client.post("xxx3", data=req_data)
        print "retcode: " + str(r.status_code)
        print "content: " + r.text
        assert r.status_code == 200

class websitUser(HttpLocust):
    task_set = testBroadBand
    min_wait = 5000
    max_wait = 8000