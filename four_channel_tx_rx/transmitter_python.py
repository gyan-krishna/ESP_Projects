# -*- coding: utf-8 -*-
"""
----------Phenix Labs----------
Created on Thu May 27 21:29:03 2021
@author: Gyan Krishna

Topic:
"""

from tkinter import *
import urllib.request
import http
import random
import time

base = r'http://192.168.0.105/'

def transfer(data):   #use to send and receive data
    try:
        n = urllib.request.urlopen(base + data).read()
        n = n.decode("utf-8")

        return n

    except http.client.HTTPException as e:
        return str(e)

def generate_data(data):
    ret = ""
    for dat in data:
        ret = ret + str(dat) + "_"
    return ret

def callback(val):
    data = [slider1.get(),slider2.get(),slider3.get(),slider4.get()]
    resp = transfer(generate_data(data))
    print(resp)

def activateCallBack():
    if(actButton['text'] == "deactivate"):
        resp = transfer("deactivate")
        if(resp == "deactivated"):
            actButton['text'] = "activate"
    else:
        resp = transfer("activate")
        if(resp == "activated"):
            actButton['text'] = "deactivate"
        else:
            print("error", str(resp))

    print(resp)

print("testing", transfer("test"))

win = Tk()
win.title("controller")
win.geometry('550x700')

header = Label(win, text = "RC Controller", font=("Arial Bold", 20))
header.grid(column=0, row=0)

slider1 = Scale(win, from_=0, to_=180, orient=HORIZONTAL, tickinterval=30, length = 500, label="Ch 1", command = callback)
slider1.grid(column=0, row=1)

slider2 = Scale(win, from_=0, to_=180, orient=HORIZONTAL, tickinterval=30, length = 500, label="Ch 2", command = callback)
slider2.grid(column=0, row=2)

slider3 = Scale(win, from_=0, to_=180, orient=HORIZONTAL, tickinterval=30, length = 500, label="Ch 3", command = callback)
slider3.grid(column=0, row=3)

slider4 = Scale(win, from_=0, to_=180, orient=HORIZONTAL, tickinterval=30, length = 500, label="Ch 4", command = callback)
slider4.grid(column=0, row=4)

actButton = Button(win, text="Activate", command=activateCallBack)
actButton.grid(column = 0, row = 5)

win.mainloop()
