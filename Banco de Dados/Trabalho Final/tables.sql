CREATE TABLE Membros (
	membro_id INT AUTO_INCREMENT PRIMARY KEY,
	cpf VARCHAR(20) UNIQUE NOT NULL,
	nome VARCHAR(255) NOT NULL,
	tipo ENUM('interno', 'externo') NOT NULL
);

ALTER TABLE Membros
ADD email varchar(50);

CREATE TABLE Membros_Internos(
	membro_id INT PRIMARY KEY,
	documento VARCHAR(10) UNIQUE NOT NULL,
	FOREIGN KEY (membro_id) REFERENCES Membros(membro_id)
);

CREATE TABLE Membros_Externos(
	membro_id INT PRIMARY KEY,
	afiliacao VARCHAR(255),
	FOREIGN KEY (membro_id) REFERENCES Membros(membro_id)
);

CREATE TABLE Cargo(
	cargo VARCHAR(50),
	equipe VARCHAR(20),
	PRIMARY KEY(cargo, equipe)
);

CREATE TABLE Cargo_Membro(
	membro_id INT NOT NULL,
	cargo VARCHAR(50) NOT NULL,
	equipe VARCHAR(20) NOT NULL,
	dataIni date NOT NULL,
	dataFim date,
	PRIMARY KEY(membro_id, cargo, equipe),
	FOREIGN KEY (membro_id) REFERENCES Membros(membro_id),
	FOREIGN KEY (cargo, equipe) REFERENCES Cargo(cargo, equipe)
);

CREATE TABLE Curso(
	curso VARCHAR(100),
	ano INT,
	PRIMARY KEY(curso, ano)
);

CREATE TABLE Processo_Seletivo(
	ano INT PRIMARY KEY
);

CREATE TABLE Responsavel_Curso(
	membro_id INT,
	curso VARCHAR(100),
	ano INT,
	PRIMARY KEY (membro_id, curso, ano),
	FOREIGN KEY (membro_id) REFERENCES Membros(membro_id),
	FOREIGN KEY (curso, ano) REFERENCES Curso(curso, ano)
);

CREATE TABLE Responsavel_Processo_Seletivo(
	membro_id INT,
	ano INT,
	PRIMARY KEY (membro_id, ano),
	FOREIGN KEY (membro_id) REFERENCES Membros(membro_id),
	FOREIGN KEY (ano) REFERENCES Processo_Seletivo(ano)
);

CREATE TABLE Pessoas_Externas(
	email VARCHAR(50) PRIMARY KEY,
	nome VARCHAR(255) NOT NULL
);

CREATE TABLE Participante_Externo_Curso(
	email VARCHAR(50) NOT NULL,
	curso VARCHAR(100) NOT NULL,
	ano INT NOT NULL,
	PRIMARY KEY (email, curso, ano),
	FOREIGN KEY (email) REFERENCES Pessoas_Externas(email),
	FOREIGN KEY (curso, ano) REFERENCES Curso(curso, ano)
);

CREATE TABLE Participante_Membro_Curso(
	membro_id INT NOT NULL,
	curso VARCHAR(100) NOT NULL,
	ano INT NOT NULL,
	PRIMARY KEY (membro_id, curso, ano),
	FOREIGN KEY (membro_id) REFERENCES Membros(membro_id),
	FOREIGN KEY (curso, ano) REFERENCES Curso(curso, ano)
);

CREATE TABLE Eventos(
	nome VARCHAR(100) NOT NULL,
	edicao VARCHAR(100) NOT NULL,
	ano INT NOT NULL,
	PRIMARY KEY (nome, edicao, ano)
);

CREATE TABLE Artigo(
	DOI VARCHAR(50) PRIMARY KEY,
	artigo VARCHAR(255) NOT NULL,
	ano INT NOT NULL
);

CREATE TABLE Jogos(
	titulo VARCHAR(255) PRIMARY KEY,
	ano INT NOT NULL,
	materia VARCHAR(255),
	conteudo VARCHAR(255)
);

CREATE TABLE Participacao_Evento(
	membro_id INT NOT NULL,
	nome VARCHAR(100) NOT NULL,
	edicao VARCHAR(100) NOT NULL,
	ano INT NOT NULL,
	PRIMARY KEY (membro_id, nome, edicao, ano),
	FOREIGN KEY (membro_id) REFERENCES Membros(membro_id),
	FOREIGN KEY (nome, edicao, ano) REFERENCES Eventos(nome, edicao, ano)
);

CREATE TABLE Autoria_Artigo(
	DOI VARCHAR(50) NOT NULL,
	membro_id INT NOT NULL,
	PRIMARY KEY (DOI, membro_id),
	FOREIGN KEY (DOI) REFERENCES Artigo(DOI),
	FOREIGN KEY (membro_id) REFERENCES Membros(membro_id)
);

CREATE TABLE Membro_Desenvolvimento(
	membro_id INT NOT NULL,
	titulo VARCHAR(255) NOT NULL,
	PRIMARY KEY (membro_id, titulo),
	FOREIGN KEY (membro_id) REFERENCES Membros(membro_id),
	FOREIGN KEY (titulo) REFERENCES Jogos(titulo)
);