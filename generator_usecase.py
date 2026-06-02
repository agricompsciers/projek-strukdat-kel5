import random
from datetime import datetime, timedelta

jenis_kegiatan = ["Rapat", "Seminar", "Kuliah", "Presentasi", "Workshop"]
subjek_kegiatan = ["AI", "Robotik", "Statistika", "Pemrograman", "Cyber", "Riset"]
nama_ruang = ["R101", "R102", "R103", "R104", "R105", "R106", "R107"]

file_path = "test_cases.txt"

with open(file_path, "w") as file:
    for i in range(1000):
        
        menu_choice = random.randint(1, 4)
        
        if menu_choice == 1: 
            room_id = random.randint(1, 1000)
            nama = f"{random.choice(jenis_kegiatan)}{random.choice(subjek_kegiatan)}"
            ruang = random.choice(nama_ruang)
            start_hour = random.randint(8, 17)
            end_hour = start_hour + random.randint(1, 3)
            
            start_date = datetime(2026, 1, 1)
            random_days = random.randint(0, 365)
            tanggal = (start_date + timedelta(days=random_days)).strftime("%Y-%m-%d")
            
            file.write(f"1\n{room_id}\n{nama}\n{ruang}\n{start_hour}\n{end_hour}\n{tanggal}\nAktif\n")
            
        elif menu_choice == 2: 
            ruang = random.choice(nama_ruang)
            file.write(f"2\n{ruang}\n")
            
        elif menu_choice == 3:
            room_id = random.randint(1, 1000)
            nama_baru = f"Update{random.choice(subjek_kegiatan)}"
            start_hour = random.randint(8, 17)
            end_hour = start_hour + random.randint(1, 2)
            
            file.write(f"3\n{room_id}\n{nama_baru}\n{start_hour}\n{end_hour}\n")
            
        elif menu_choice == 4:
            room_id = random.randint(1, 1000)
            file.write(f"4\n{room_id}\n")

    file.write("5\n")

print(f"Generated test cases in {file_path}")