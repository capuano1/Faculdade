INSERT INTO Membros (cpf, nome, tipo) VALUES ("111.222.333-45", "Vanessa Andrade Pereira", "interno");
INSERT INTO Membros (cpf, nome, tipo) VALUES ("123.456.789-10", "Thiago Corso Capuano", "interno");
INSERT INTO Membros (cpf, nome, tipo) VALUES ("789.456.123-01", "Guilherme Sabbado", "interno");
INSERT INTO Membros (cpf, nome, tipo) VALUES ("321.654.987-01", "Cassiano Paiva", "interno");
INSERT INTO Membros (cpf, nome, tipo) VALUES ("456.123.789-45", "Matheus Dyonisio", "interno");
INSERT INTO Membros (cpf, nome, tipo) VALUES ("654.321.333-45", "Leticia Shiotani", "interno");
INSERT INTO Membros (cpf, nome, tipo) VALUES ("000.000.000-01", "Geisse Costa", "interno");
INSERT INTO Membros (cpf, nome, tipo) VALUES ("432.763.432-22", "Sara Elisie", "externo");
INSERT INTO Membros (cpf, nome, tipo) VALUES ("654.123.765-10", "Aline Souza", "externo");
INSERT INTO Membros (cpf, nome, tipo) VALUES ("824.734.284-54", "Lilian Carvalho", "interno");
INSERT INTO Membros (cpf, nome, tipo) VALUES ("765.345.654-12", "Rodrigo Dias", "interno");
INSERT INTO Membros (cpf, nome, tipo) VALUES ("876.654.123-65", "Vinicius Mello", "interno");

UPDATE Membros
SET email="vapereira@unifesp.br"
WHERE membro_id=1;;

UPDATE Membros
SET email="thiago.capuano@unifesp.br"
WHERE membro_id=2;

UPDATE Membros
SET email="alisouza@gmail.com"
WHERE membro_id=9;

INSERT INTO Membros_Internos VALUES (1, "0274285");
INSERT INTO Membros_Internos VALUES (2, "163996");
INSERT INTO Membros_Internos VALUES (3, "162384");
INSERT INTO Membros_Internos VALUES (4, "152387");
INSERT INTO Membros_Internos VALUES (5, "178346");
INSERT INTO Membros_Internos VALUES (6, "162954");
INSERT INTO Membros_Internos VALUES (7, "173894");
INSERT INTO Membros_Internos VALUES (10, "174378");
INSERT INTO Membros_Internos VALUES (11, "126534");
INSERT INTO Membros_Internos VALUES (12, "156276");

INSERT INTO Membros_Externos VALUES (8, "Unifesp");
INSERT INTO Membros_Externos VALUES (9, "EMEFI Professora Maria Aparecida Dos Santos Ronconi");

INSERT INTO Cargo VALUES ("Coordenador Docente", "Administração");
INSERT INTO Cargo VALUES ("Membro", "Pesquisa");
INSERT INTO Cargo VALUES ("Coordenador Discente", "Administração");
INSERT INTO Cargo VALUES ("Membro", "Arte");
INSERT INTO Cargo VALUES ("Membro", "Marketing");
INSERT INTO Cargo VALUES ("Membro (Mestrado)", "Pesquisa");
INSERT INTO Cargo VALUES ("Capitão", "Tester");
INSERT INTO Cargo VALUES ("Capitão", "Programação");
INSERT INTO Cargo VALUES ("Membro", "Programação");

INSERT INTO Cargo_Membro (membro_id, cargo, equipe, dataIni) VALUES (1, "Coordenador Docente", "Administração", '2016-01-01');
INSERT INTO Cargo_Membro (membro_id, cargo, equipe, dataIni) VALUES (2, "Membro", "Pesquisa", '2023-01-01');
INSERT INTO Cargo_Membro (membro_id, cargo, equipe, dataIni) VALUES (3, "Coordenador Discente", "Administração", '2022-01-01');
INSERT INTO Cargo_Membro (membro_id, cargo, equipe, dataIni) VALUES (3, "Capitão", "Tester", '2022-01-01');
INSERT INTO Cargo_Membro (membro_id, cargo, equipe, dataIni) VALUES (4, "Coordenador Discente", "Administração", '2022-01-01');
INSERT INTO Cargo_Membro (membro_id, cargo, equipe, dataIni) VALUES (5, "Membro", "Arte", '2024-01-01');
INSERT INTO Cargo_Membro (membro_id, cargo, equipe, dataIni) VALUES (6, "Membro", "Marketing", '2023-01-01');
INSERT INTO Cargo_Membro (membro_id, cargo, equipe, dataIni) VALUES (7, "Membro (Mestrado)", "Pesquisa", '2024-01-01');
INSERT INTO Cargo_Membro (membro_id, cargo, equipe, dataIni) VALUES (10, "Membro", "Arte", '2024-01-01');
INSERT INTO Cargo_Membro (membro_id, cargo, equipe, dataIni, dataFim) VALUES (11, "Capitão", "Programação", '2019-01-01', '2023-01-01');
INSERT INTO Cargo_Membro (membro_id, cargo, equipe, dataIni) VALUES (12, "Membro", "Programação", '2022-01-01');

INSERT INTO Curso VALUES ("Game Design", 2024);
INSERT INTO Curso VALUES ("Unity", 2024);
INSERT INTO Curso VALUES ("Game Design", 2023);
INSERT INTO Curso VALUES ("Unity", 2023);
INSERT INTO Curso VALUES ("Game Design", 2022);
INSERT INTO Curso VALUES ("Unity", 2022);

INSERT INTO Processo_Seletivo VALUES (2024);
INSERT INTO Processo_Seletivo VALUES (2023);
INSERT INTO Processo_Seletivo VALUES (2022);

INSERT INTO Responsavel_Curso VALUES (4, "Game Design", 2024);
INSERT INTO Responsavel_Curso VALUES (4, "Game Design", 2023);
INSERT INTO Responsavel_Curso VALUES (4, "Game Design", 2022);
INSERT INTO Responsavel_Curso VALUES (3, "Unity", 2024);
INSERT INTO Responsavel_Curso VALUES (3, "Unity", 2023);
INSERT INTO Responsavel_Curso VALUES (12, "Unity", 2023);
INSERT INTO Responsavel_Curso VALUES (11, "Unity", 2022);

INSERT INTO Responsavel_Processo_Seletivo VALUES (3, 2024);
INSERT INTO Responsavel_Processo_Seletivo VALUES (4, 2023);
INSERT INTO Responsavel_Processo_Seletivo VALUES (1, 2022);

INSERT INTO Pessoas_Externas VALUES ("fulano@gmail.com", "Fulano da Silva");
INSERT INTO Pessoas_Externas VALUES ("ciclano@hotmail.com", "Ciclano Souza");
INSERT INTO Pessoas_Externas VALUES ("maria@gmail.com", "Maria Silva");
INSERT INTO Pessoas_Externas VALUES ("chiquinha@hotmail.com", "Chiquinha Oliveira");
INSERT INTO Pessoas_Externas VALUES ("alice@terra.com", "Alice Silveira");
INSERT INTO Pessoas_Externas VALUES ("raul@bol.com", "Raul Seixas");
INSERT INTO Pessoas_Externas VALUES ("sergio@terra.com", "Sergio Capuano");
INSERT INTO Pessoas_Externas VALUES ("lucas@hotmail.com", "Lucas Terra");
INSERT INTO Pessoas_Externas VALUES ("rafael@hotmail.com", "Rafael Louro");
INSERT INTO Pessoas_Externas VALUES ("tomas@hotmail.com", "Tomas Lincoln");

INSERT INTO Participante_Externo_Curso VALUES ("fulano@gmail.com", "Unity", 2024);
INSERT INTO Participante_Externo_Curso VALUES ("ciclano@hotmail.com", "Game Design", 2023);
INSERT INTO Participante_Externo_Curso VALUES ("maria@gmail.com", "Unity", 2023);
INSERT INTO Participante_Externo_Curso VALUES ("chiquinha@hotmail.com", "Game Design", 2022);
INSERT INTO Participante_Externo_Curso VALUES ("alice@terra.com", "Unity", 2024);
INSERT INTO Participante_Externo_Curso VALUES ("raul@bol.com", "Unity", 2022);
INSERT INTO Participante_Externo_Curso VALUES ("sergio@terra.com", "Unity", 2023);
INSERT INTO Participante_Externo_Curso VALUES ("lucas@hotmail.com", "Game Design", 2024);
INSERT INTO Participante_Externo_Curso VALUES ("rafael@hotmail.com", "Unity", 2022);
INSERT INTO Participante_Externo_Curso VALUES ("tomas@hotmail.com", "Game Design", 2023);

INSERT INTO Participante_Membro_Curso VALUES (2, "Game Design", 2023);
INSERT INTO Participante_Membro_Curso VALUES (7, "Unity", 2023);

INSERT INTO Eventos VALUES ("Science Days", "Parque da Cidade", 2023);
INSERT INTO Eventos VALUES ("Science Days", "Parque Tecnológico", 2024);

INSERT INTO Artigo VALUES ("10.1590/1984-6398202017555", "Example Article: Games", 2022);

INSERT INTO Jogos VALUES ("Matemágica", 2021, "Matemática", "4 Operações Básicas");
INSERT INTO Jogos VALUES ("Cidade dos Sinais", 2022, "GAAL", "Cotidiano: Sinais, Transporte...");
INSERT INTO Jogos VALUES ("Tempo Voa", 2023, "Matemática", "Tempo e Relógio");

INSERT INTO Participacao_Evento VALUES (1, "Science Days", "Parque da Cidade", 2023);
INSERT INTO Participacao_Evento VALUES (1, "Science Days", "Parque Tecnológico", 2024);
INSERT INTO Participacao_Evento VALUES (2, "Science Days", "Parque da Cidade", 2023);
INSERT INTO Participacao_Evento VALUES (2, "Science Days", "Parque Tecnológico", 2024);
INSERT INTO Participacao_Evento VALUES (3, "Science Days", "Parque da Cidade", 2023);
INSERT INTO Participacao_Evento VALUES (3, "Science Days", "Parque Tecnológico", 2024);
INSERT INTO Participacao_Evento VALUES (4, "Science Days", "Parque da Cidade", 2023);
INSERT INTO Participacao_Evento VALUES (4, "Science Days", "Parque Tecnológico", 2024);

INSERT INTO Autoria_Artigo VALUES ("10.1590/1984-6398202017555", 2);
INSERT INTO Autoria_Artigo VALUES ("10.1590/1984-6398202017555", 3);
INSERT INTO Autoria_Artigo VALUES ("10.1590/1984-6398202017555", 7);
INSERT INTO Autoria_Artigo VALUES ("10.1590/1984-6398202017555", 8);
INSERT INTO Autoria_Artigo VALUES ("10.1590/1984-6398202017555", 9);

INSERT INTO Membro_Desenvolvimento VALUES (3, "Tempo Voa");
INSERT INTO Membro_Desenvolvimento VALUES (4, "Cidade dos Sinais");
INSERT INTO Membro_Desenvolvimento VALUES (11, "Matemágica");
INSERT INTO Membro_Desenvolvimento VALUES (12, "Cidade dos Sinais");
INSERT INTO Membro_Desenvolvimento VALUES (12, "Tempo Voa");