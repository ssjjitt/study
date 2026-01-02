CREATE TABLE "Specializations" (
    "id" NUMBER NOT NULL,
    "spec_kode" NVARCHAR2(255) NOT NULL,
    "faculty_id" NUMBER NOT NULL,
    "department_id" NUMBER NOT NULL,
    "fullName" NVARCHAR2(255) NOT NULL,
    "shortName" NVARCHAR2(255) NOT NULL
);

ALTER TABLE "Specializations" ADD CONSTRAINT "specializations_id_primary" PRIMARY KEY ("id");

CREATE UNIQUE INDEX "specialization" ON "Specializations" ("spec_kode");

CREATE TABLE "teachers_salary" (
    "id" NUMBER NOT NULL,
    "start_date" DATE NOT NULL,
    "end_date" DATE NOT NULL,
    "work_time" NUMBER NOT NULL,
    "salary" NUMBER NOT NULL,
    "teacher_id" NUMBER NOT NULL
);