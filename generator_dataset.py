import random
import os
from datetime import datetime, timedelta

jenis_kegiatan = [
    "Rapat", "Seminar", "Kuliah", "Presentasi", "Workshop"
]
subjek_kegiatan = [
    "AI", "Robotik", "Statistika", "Pemrograman", 
    "Cyber", "Riset", "RPL", "Teknologi", "Manajemen"
]
nama_ruang = [
    "R101", "R102", "R103", "R104", "R105", "R106", "R107"
]

file_path = "jadwal.txt"

booked_slots = {}

with open(file_path, "w") as file:
    for i in range(1000):
        room_id = i + 1

        random_jenis = random.choice(jenis_kegiatan)
        random_subjek = random.choice(subjek_kegiatan)

        while True:
            random_room = random.choice(nama_ruang)

            start_hour = random.randint(8, 20)
            end_hour = start_hour + random.randint(1, 3)

            start_date = datetime(2026, 1, 1)   
            end_date = datetime(2026, 12, 31)  
            days_between = (end_date - start_date).days
            random_days = random.randint(0, days_between)
            
            result_date = start_date + timedelta(days=random_days)
            random_date = result_date.strftime("%Y-%m-%d")

            conflict = False
            if (random_room, random_date) in booked_slots:
                for b_start, b_end in booked_slots[(random_room, random_date)]:
                    if start_hour < b_end and end_hour > b_start:
                        conflict = True
                        break
            
            if not conflict:
                if (random_room, random_date) not in booked_slots:
                    booked_slots[(random_room, random_date)] = []
                booked_slots[(random_room, random_date)].append((start_hour, end_hour))
                break

        status = "aktif"

        file.write(f"{room_id} {random_jenis}{random_subjek} {random_room} {start_hour} {end_hour} {random_date} {status}\n")

print(f"Generated 1000 rows of data in {file_path}")