--Ronna Database

CREATE TABLE IF NOT EXISTS 'SchemaInfo' (
  'Version' TEXT NOT NULL );

INSERT INTO 'SchemaInfo' VALUES('0.0.1');

CREATE TABLE IF NOT EXISTS 'Patients' (
  'UID'               INTEGER PRIMARY KEY,
  'PatientName'       TEXT NULL,
  'PatientID'         TEXT NULL,
  'PatientBirthDate'  TEXT NULL,
  'PatientBirthTime'  TEXT NULL,
  'PatientSex'        TEXT NULL,
  'PatientAge'        TEXT NULL);

CREATE TABLE IF NOT EXISTS 'Studies' (
  'StudyInstanceUID'          TEXT NOT NULL,
  'StudyID'                   TEXT NULL,
  'StudyDate'                 TEXT NULL,
  'StudyTime'                 TEXT NULL,
  'AccessionNumber'           TEXT NULL, --order of the study
  'PatientUID'                INTEGER NOT NULL,
  CHECK(length('StudyInstanceUID') > 0),
  PRIMARY KEY ('StudyInstanceUID'),
  FOREIGN KEY ('PatientUID') REFERENCES 'Patients' ('UID') );
  
CREATE TABLE IF NOT EXISTS 'Series' (
  'SeriesInstanceUID'     TEXT NOT NULL,
  'SeriesNumber'          TEXT NULL,
  'SeriesDate'            DATE NULL,
  'SeriesTime'            TEXT NULL,
  'SeriesDescription'     TEXT NULL,
  'Modality'              TEXT NULL,
  'BodyPartExamined'      TEXT NULL,
  'StudyInstanceUID'      TEXT NOT NULL,
  CHECK(length('SeriesInstanceUID') > 0),
  PRIMARY KEY ('SeriesInstanceUID'),
  FOREIGN KEY ('StudyInstanceUID') REFERENCES 'Studies' ('StudyInstanceUID') );

CREATE TABLE IF NOT EXISTS 'Images' (
  'SOPInstanceUID'      TEXT NOT NULL,
  'Filename'            TEXT NOT NULL,
  'SeriesInstanceUID'   TEXT NOT NULL,
  CHECK(length('SOPInstanceUID') > 0),
  PRIMARY KEY ('SOPInstanceUID') );

CREATE TABLE IF NOT EXISTS 'OperationPlans' (
  'UID'                 INTEGER PRIMARY KEY,
  'PlanJson'            TEXT NOT NULL,
  'SeriesInstanceUID'   TEXT NOT NULL,
  'PlanName'   TEXT NOT NULL,
  FOREIGN KEY ('SeriesInstanceUID') REFERENCES 'Series' ('SeriesInstanceUID')
);

CREATE UNIQUE INDEX IF NOT EXISTS 'ImagesFilenameIndex'   ON 'Images'   ('Filename');
CREATE INDEX IF NOT EXISTS        'ImagesSeriesIndex'     ON 'Images'   ('SeriesInstanceUID');
CREATE INDEX IF NOT EXISTS        'SeriesStudyIndex'      ON 'Series'   ('StudyInstanceUID');
CREATE INDEX IF NOT EXISTS        'StudiesPatientIndex'   ON 'Studies'  ('PatientUID');
