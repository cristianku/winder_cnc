from tkinter import *
from tkinter.ttk import Combobox

from tkinter import messagebox

import argparse
import time

from tqdm import tqdm

import serial

import os

import serial.tools.list_ports

class GRBL_Connection:
  def __init__(self, dev_serial):
      self.dev_serial = dev_serial
      self.SERIAL_CONNECTION = serial.Serial(self.dev_serial, 115200)
      self.SERIAL_CONNECTION.write(str.encode("\r\n\r\n"))
      time.sleep(2)  # Wait for initialization
      self.SERIAL_CONNECTION.flushInput()  # Flush startup text in serial input
      self.send_Gcode("G91")
      
  def send_Gcode(self, cmd_gcode):
      # print('Sending: ' + cmd_gcode)
      self.SERIAL_CONNECTION.write(cmd_gcode.encode() + str.encode('\n'))  # Send g-code block
      # Wait for response with carriage return
      self.grbl_out = self.SERIAL_CONNECTION.readline()
      # print(self.grbl_out.strip().decode("utf-8"))
      return self.grbl_out.strip().decode("utf-8")


class MyWindow:
    def __init__(self, win):
        self.img = PhotoImage(file="background2.png")
        self.label = Label(
            win,
            image=self.img
        )
        self.label.place(x=0, y=0)
        #
        # var = StringVar()
        # lbl = Label(window, text="Here you can generate the GCODE file for the GRBL winding machine",  font=("Helvetica", 16))
        # lbl.place(x=100, y=50)

        # lbl2 = Label(window, text="2022 Copyright Z MUSIC Corp.",  font=("Helvetica", 16))
        # lbl2.place(x=100, y=650)

        # var.set("Scatter level 1")
        # data = ("Scatter level 1", "Scatter level 2", "Scatter level 3", "Scatter level 4")
        # self.lb = Listbox(window, height=5, selectmode='single')
        # for num in data:
        #    self.lb.insert(END, num)
        # self.lb.place(x=450, y=150)
        # self.lb.select_set(0)



        self.lbl1=Label(win, text='Turns')
        self.lbl1.place(x=100, y=150)

        self.lbl2=Label(win, text='0%')
        # self.lbl3=Label(win, text='Result')
        self.t1=Entry(text='8000', bd=3)
        self.t1.delete(0, END)
        self.t1.insert(0, '100')
        self.t1.bind("<KeyRelease>", self.OnEntryT1Click)

        # self.t2=Entry()

        # self.btn1 = Button(win, text='Generate')
        self.t1.place(x=200, y=150)
        # self.lbl2.place(x=550, y=250)
        # self.t2.place(x=550, y=250)
        # self.b1=Button(win, text='Generate', command=self.generate)
        self.b2=Button(win, text='Run to Winder', command=self.run_winder)

        # self.b2=Button(win, text='Subtract')
        # self.b2.bind('<Button-1>', self.sub)
        # self.b1.place(x=650, y=350)
        self.b2.place(x=530, y=243)

        self.lbl_turns_completed=Label(win, text='Completed Turns')
        self.lbl_turns_completed.place(x=530, y=150)

        self.lbl_turns_completed=Label(win, text='Forseen total turns: ')
        self.lbl_turns_completed.place(x=530, y=180)


        self.t_completed=Entry(text='7000', bd=2)
        self.t_completed.delete(0, END)
        self.t_completed.insert(0, '0')
        self.t_completed.place(x=650, y=150)
        self.t_completed.bind("<KeyRelease>", self.OnEntryT1Click)

        self.zero_completed_b=Button(win, text='set to 0', command=self.zero_completed)
        self.zero_completed_b.place(x=850, y=150)


        # self.b2.place(x=200, y=150)
        # self.lbl3.place(x=100, y=200)
        # self.t3.place(x=200, y=200)

        # self.t2.insert(END, '10%')
        # Progress bar widget
        ports_list = list()
        all_port_tuples = serial.tools.list_ports.comports()
        for ap, _, _ in all_port_tuples:
            # print(ap)
            if "usb" in ap:
              ports_list.append(ap)

        self.choose_port = Combobox(window, width=40, height=5, values=ports_list)
        # for port in serial.tools.list_ports.comports():
        #     self.choose_port.insert(END, port)
        self.choose_port.place(x=250, y=450)
        if ports_list:
            self.choose_port.current(0)
        
        # self.lbl1=Label(win, text='Port')
        # self.lbl1.place(x=100, y=450)

        self.refresh_ports_button=Button(win, text='Refresh Ports', command=self.refresh_ports())
        self.refresh_ports_button.place(x=100, y=450)

        # Select winding speed
        winding_speed_list = ("300","700","600","500","400")
        self.winding_speed = Combobox(win, width=20, height=5, values=winding_speed_list,textvariable = 'n')
        self.winding_speed.place(x=200, y=350)
        self.winding_speed.current(0)

        self.lbl1=Label(win, text='Speed')
        self.lbl1.place(x=100, y=350)

        # Scatter level
        self.lbl_scatter=Label(win, text='Scatter Level')
        self.lbl_scatter.place(x=100, y=250)

        self.scatter_level_scale = Scale(win, from_=0, to=4, orient=HORIZONTAL)
        self.scatter_level_scale.set(1)
        self.scatter_level_scale.pack()
        self.scatter_level_scale.place(x=200, y=230)
        self.scatter_level_scale.bind("<ButtonRelease-1>", self.updateScaleValue)

        self.lbl_scatter_2=Label(win, text=self.get_lbl_scatter_2(self.scatter_level_scale.get()))
        self.lbl_scatter_2.place(x=100, y=280)

        self.updateForseenTotTurns()

    def OnEntryT1Click(self,event):
        self.updateForseenTotTurns()
        return True
    
    def get_lbl_scatter_2(self, scatter_level):
        turns = self.get_Turns_per_scatter_level(scatter_level)
        if scatter_level == 1:
          return "Level 1 - most scattered   ( min. {} turns )".format(turns)
        elif scatter_level == 2:
          return "Level 2 - medium scattered ( min. {} turns )".format(turns)
        elif scatter_level == 3:
          return "Level 3 - least scattered  ( min. {} turns )".format(turns)
        elif scatter_level == 4:
          return "Level 4 - Mix of High and Low scatter ( Level 1 + 3 )  ( {} turns )".format(turns)
        elif scatter_level == 0:
          return "Final touches: just 50 turns ( {} turns )".format(turns)

    def UpdateCompletedTurns(self,turns_per_iteration):
        completed_turns = int(self.t_completed.get()) + turns_per_iteration
        self.t_completed.delete(0, END)
        self.t_completed.insert(0, "{}".format(completed_turns))
        print(" Completed turns : {}".format(completed_turns))

    def get_Turns_per_scatter_level(self,scatter_level):
        if scatter_level == 1:
          return 100
        elif scatter_level == 2:
          return 200
        elif scatter_level == 3:
          return 350
        elif scatter_level == 4:
          return 900
        elif scatter_level == 0:
          return 50


    def updateScaleValue(self, event):
        scatter_level = self.scatter_level_scale.get()
        Turns_per_scatter_level = int(self.get_Turns_per_scatter_level(scatter_level))

        self.lbl_scatter_2.config(text=self.get_lbl_scatter_2(scatter_level))
        # self.t_completed.delete(0, END)
        # self.t_completed.insert(0, "{}".format(self.scatter_level_scale.get()))
        self.t1.delete(0, END)
        self.t1.insert(0, "{}".format(Turns_per_scatter_level ) )

        self.lbl_turns_completed.config(text="Forseen total turns: {}".format(Turns_per_scatter_level + int(self.t_completed.get()) ))

    def updateForseenTotTurns(self):
        scatter_level = self.scatter_level_scale.get()
        bobbin_turns = int(self.t1.get())
        Turns_per_scatter_level = int(self.get_Turns_per_scatter_level(scatter_level))
        possible_turns = int(bobbin_turns/ Turns_per_scatter_level) * Turns_per_scatter_level

        self.lbl_turns_completed.config(text="Forseen total turns: {}".format(possible_turns + int(self.t_completed.get()) ))

    def refresh_ports(self):
        print ( " refresh ports ")
        ports_list = list()
        all_port_tuples = serial.tools.list_ports.comports()
        for ap, _, _ in all_port_tuples:
            # print (ap)
            if "usb" in ap:
                ports_list.append(ap)
        self.choose_port['values'] = ports_list
        if ports_list:
            self.choose_port.current(0)

    def generate(self):
        self.execute_process(False)

    def run_winder(self):
        if self.choose_port.get():
            self.execute_process(True)
        else:
            messagebox.showinfo(title='Error', message='USB connection undefined')

    def zero_completed(self):
        self.t_completed.delete(0, END)
        self.t_completed.insert(0, "{}".format())

    def execute_process(self, runWinder ):

        # scatter_level = int()
        # for item in self.lb.curselection():
        #     scatter_level = int(item + 1)
        scatter_level = int(self.scatter_level_scale.get())
        print ( scatter_level)

        usb_connection_string = self.choose_port.get()
        # print(usb_connection_string)
        winding_speed = self.winding_speed.get()


        if not (len(self.t1.get()) == 0 ) and  scatter_level:
          
            bobbin_turns = int(self.t1.get())

            START_TIME = time.time()
            turns_per_iteration = int(self.get_Turns_per_scatter_level(scatter_level))
            print("turns per iteration: {}".format(turns_per_iteration))
            iterations = int(bobbin_turns / turns_per_iteration)
            print("iterations: {}".format(iterations))

            GRBL = GRBL_Connection(usb_connection_string)

            if scatter_level == 1:
                print("entering scatter level 1")

                for i in range(iterations):

                    GRBL.send_Gcode("G1 X30 Y0.9 F{}".format(winding_speed))
                    GRBL.send_Gcode("G1 X30 Y-0.9 F{}".format(winding_speed))

                    GRBL.send_Gcode("G1 X15 Y0.9 F{}".format(winding_speed))
                    GRBL.send_Gcode("G1 X15 Y-0.9 F{}".format(winding_speed))

                    GRBL.send_Gcode("G1 X5 Y0.9 F{}".format(winding_speed))
                    GRBL.send_Gcode("G1 X5 Y-0.9 F{}".format(winding_speed))
                    self.UpdateCompletedTurns(turns_per_iteration)


            elif scatter_level == 2:
                print("entering scatter level 2")

                for i in range(iterations):

                    GRBL.send_Gcode("G1 X50 Y0.9 F{}".format(winding_speed))
                    GRBL.send_Gcode("G1 X50 Y-0.9 F{}".format(winding_speed))

                    GRBL.send_Gcode("G1 X30 Y0.9 F{}".format(winding_speed))
                    GRBL.send_Gcode("G1 X30 Y-0.9 F{}".format(winding_speed))

                    GRBL.send_Gcode("G1 X20 Y0.9 F{}".format(winding_speed))
                    GRBL.send_Gcode("G1 X20 Y-0.9 F{}".format(winding_speed))
                    self.UpdateCompletedTurns(turns_per_iteration)


            elif scatter_level == 3:
                print("entering scatter level 3")

                for i in range(iterations):
                    GRBL.send_Gcode("G1 X100 Y0.9 F{}".format(winding_speed))
                    GRBL.send_Gcode("G1 X100 Y-0.9 F{}".format(winding_speed))

                    GRBL.send_Gcode("G1 X50 Y0.9 F{}".format(winding_speed))
                    GRBL.send_Gcode("G1 X50 Y-0.9 F{}".format(winding_speed))

                    GRBL.send_Gcode("G1 X25 Y0.9 F{}".format(winding_speed))
                    GRBL.send_Gcode("G1 X25 Y-0.9 F{}".format(winding_speed))

                    self.UpdateCompletedTurns(turns_per_iteration)


            elif scatter_level == 4:
                print("entering scatter level 4")

                for i in range(iterations):
                    # scatter level 3 - 350 turns

                    GRBL.send_Gcode("G1 X100 Y0.9 F{}".format(winding_speed))
                    GRBL.send_Gcode("G1 X100 Y-0.9 F{}".format(winding_speed))

                    GRBL.send_Gcode("G1 X50 Y0.9 F{}".format(winding_speed))
                    GRBL.send_Gcode("G1 X50 Y-0.9 F{}".format(winding_speed))

                    GRBL.send_Gcode("G1 X25 Y0.9 F{}".format(winding_speed))
                    GRBL.send_Gcode("G1 X25 Y-0.9 F{}".format(winding_speed))

                    # scatter level 1 - 100 turns repeated 2 times
                    # first repeat
                    GRBL.send_Gcode("G1 X30 Y0.9 F{}".format(winding_speed))
                    GRBL.send_Gcode("G1 X30 Y-0.9 F{}".format(winding_speed))

                    GRBL.send_Gcode("G1 X15 Y0.9 F{}".format(winding_speed))
                    GRBL.send_Gcode("G1 X15 Y-0.9 F{}".format(winding_speed))

                    GRBL.send_Gcode("G1 X5 Y0.9 F{}".format(winding_speed))
                    GRBL.send_Gcode("G1 X5 Y-0.9 F{}".format(winding_speed))

                    # second repeat
                    GRBL.send_Gcode("G1 X30 Y0.9 F{}".format(winding_speed))
                    GRBL.send_Gcode("G1 X30 Y-0.9 F{}".format(winding_speed))

                    GRBL.send_Gcode("G1 X15 Y0.9 F{}".format(winding_speed))
                    GRBL.send_Gcode("G1 X15 Y-0.9 F{}".format(winding_speed))

                    GRBL.send_Gcode("G1 X5 Y0.9 F{}".format(winding_speed))
                    GRBL.send_Gcode("G1 X5 Y-0.9 F{}".format(winding_speed))

                   #scatter level 3 - 350 turns

                    GRBL.send_Gcode("G1 X100 Y0.9 F{}".format(winding_speed))
                    GRBL.send_Gcode("G1 X100 Y-0.9 F{}".format(winding_speed))

                    GRBL.send_Gcode("G1 X50 Y0.9 F{}".format(winding_speed))
                    GRBL.send_Gcode("G1 X50 Y-0.9 F{}".format(winding_speed))

                    GRBL.send_Gcode("G1 X25 Y0.9 F{}".format(winding_speed))
                    GRBL.send_Gcode("G1 X25 Y-0.9 F{}".format(winding_speed))

                    self.UpdateCompletedTurns(turns_per_iteration)


            elif scatter_level == 0:
                print("entering scatter level 0")

                for i in range(iterations):

                    GRBL.send_Gcode("G1 X25 Y0.9 F{}".format(winding_speed))
                    GRBL.send_Gcode("G1 X25 Y-0.9 F{}".format(winding_speed))

                    self.UpdateCompletedTurns(turns_per_iteration)

                # f.write("; Iteration:{}".format(i+ 1) + "\n")
#                     f.write("G1 X2 Y0.9 F{};".format(winding_speed) + "\n")
#                     f.write("G1 X2 Y-0.9 F{};".format(winding_speed) + "\n")
#                     f.write("" + "\n")
#             completed_turns = int(self.t_completed.get() )
#             completed_turns = completed_turns + bobbin_turns
#             self.t_completed.delete(0, END)
#             self.t_completed.insert(0, "{}".format(completed_turns))
#             messagebox.showinfo(title='Error', message='Completed.')
            self.updateForseenTotTurns()
        else:
            messagebox.showinfo(title='Error', message='Please enter all the required fields')


window=Tk()
mywin=MyWindow(window)
window.title('Winding Machine Gcode generator')
window.geometry("1024x600+500+500")
window.mainloop()

