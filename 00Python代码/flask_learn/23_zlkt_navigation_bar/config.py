#encoding: utf-8
import os

DEBUG = True

# 生成随机24个字符
SECRET_KEY = os.urandom(24)

# 数据库配置信息
HOSTNAME = '127.0.0.1'
PORT     = '3306'
DATABASE = 'zlktqa_demo'
USERNAME = 'root'
PASSWORD = 'root'
DB_URI = 'mysql+mysqldb://{}:{}@{}:{}/{}?charset=utf8'.format(USERNAME,PASSWORD,HOSTNAME,PORT,DATABASE)
SQLALCHEMY_DATABASE_URI = DB_URI

SQLALCHEMY_TRACK_MODIFICATIONS = True
