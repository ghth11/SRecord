# SRecord
Student record system using Qt C++
This cpde was created using Qt creater and C++ programming language as a desktop application which starts with home page by starting Srecord.pro.
The inerfaceing language is Arabic.
After satarting the application there will be a button the add new student to the database named sinfo table sinfo3. The student is added using the form or by uploading a csv file that should include the reguired field. The follwing code will create the table with sqlite browser as follows:
-- sinfo3 definition
CREATE TABLE "sinfo3" (
	"sid"	INTEGER NOT NULL,
	"Names"	TEXT NOT NULL,
	"Surname"	TEXT,
	"Enname"	TEXT,
	"Gender"	TEXT,
	"dob"	TEXT,
	"mothername"	TEXT,
	"bloodtype"	TEXT,
	"idno"	TEXT,
	"phone"	TEXT,
	"parantsphone"	TEXT,
	"enrolyear"	TEXT,
	"prepschool"	TEXT,
	"Stage"	TEXT,
	"graduation"	TEXT,
	"graduationyear"	TEXT,
	"continuity"	TEXT,
	"state"	TEXT,
	"email"	TEXT,
	"pass"	TEXT,
	"y2enrol"	TEXT,
	"entership"	TEXT,
	"address"	TEXT,
	"Fullnames"	TEXT,
	"sno"	TEXT,
	"refadded"	TEXT,
	"refrendom1"	TEXT,
	"satifiedsubj"	TEXT,
	"notes"	TEXT,
	"para"	TEXT,
	"enrollment"	TEXT,
	"enroldate"	TEXT,
	"SIDNo"	TEXT,
	"IDdate"	TEXT,
	"cmback"	TEXT,
	"field36"	TEXT,
	PRIMARY KEY("sid" AUTOINCREMENT)
);
