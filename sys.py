import cx_Oracle
import os

username = ' ' #Enter your system name
password = ' ' #Enter your password

connection = cx_Oracle.connect(username, password, 'localhost:1521/xe')
cursor = connection.cursor()

from flask import Flask, render_template

app = Flask(__name__)

@app.route('/')
def index():
    # total bookings
    cursor.execute('SELECT COUNT(BOOKING_ID) FROM BOOKINGS')
    result=cursor.fetchall()
    data=result[0][0]

    # profit
    cursor.execute('''SELECT (SUM(ROOM_PRICE)+SUM(AMOUNT))FROM BOOKINGS JOIN ROOM 
    ON BOOKINGS.ROOM_NUMBER=ROOM.ROOM_NUMBER JOIN ROOM_CATEGORY 
    ON ROOM_CATEGORY.CATEGORY_ID=ROOM.TYPE_ID JOIN MEAL ON BOOKINGS.MEAL_ID=MEAL.MEAL_ID''')
    result2=cursor.fetchall()
    cursor.execute('''SELECT SUM(SALARY) FROM STAFF''')
    result7=cursor.fetchall()
    result8=3*result7[0][0] 
    profit= round(((result2[0][0]-(result8))/result8)*100,3)
    
    # monthly booking
    cursor.execute('''SELECT MONTHS_STAYED, COUNT(MONTHS_STAYED)FROM(
    SELECT EXTRACT(MONTH FROM CHECKINDATE) AS MONTHS_STAYED FROM BOOKINGS)
    GROUP BY MONTHS_STAYED
    ORDER BY MONTHS_STAYED''')
    result3=cursor.fetchall()

    # online/offline booking
    cursor.execute('''SELECT COUNT(PAYMENT_MODE)FROM BOOKINGS JOIN BILL 
    ON BOOKINGS.BOOKING_ID=BILL.BOOKING_ID 
    JOIN PAYMENT ON PAYMENT.PAYMENT_ID=BILL.PAYMENT_ID
    GROUP BY PAYMENT_MODE''')
    result4=cursor.fetchall()

    #total rooms
    cursor.execute('SELECT COUNT(ROOM_NUMBER) FROM ROOM')
    result5=cursor.fetchall()
    data5=result5[0][0]

    #avg no of days stayed
    cursor.execute('''SELECT ceil(AVG(NO_OF_DAYS_STAYED)) AS AVG_DAYS_STAYED FROM(
    SELECT TRUNC(CHECKOUTDATE-CHECKINDATE)AS NO_OF_DAYS_STAYED FROM BOOKINGS)''')
    result6=cursor.fetchall()
    data6=result6[0][0]

    
    return render_template('index.html', total_booking=data,total_profit=profit,monthly_booking=result3,on_off_booking=result4,total_rooms=data5,avg_no_of_days =data6)

@app.route('/guest')
def guest():
    return render_template('guest.html')


if __name__ == '__main__':
    app.run(debug=True)
