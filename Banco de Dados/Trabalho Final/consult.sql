-- Nem todos os membro são muito ativos no quesito comparecimento em eventos. Retorne todos os membros que já foram em algum evento
-- e o total de eventos que eles participaram
SELECT m.nome, COUNT(*) FROM Membros m JOIN Participacao_Evento pe ON (m.membro_id=pe.membro_id) GROUP BY m.nome
-- Retorna o nome e documento interno de cada membro interno
SELECT m.nome, mi.documento FROM Membros m JOIN Membros_Internos mi ON (m.membro_id=mi.membro_id)
-- Nem todos os membros fazem parte do desenvolvimento dos jogos. Liste todos os membros que já fizeram parte do desenvolvimento de
-- ao menos um dos jogos, e liste todos os jogos que ele participou e seus anos de lançamento
SELECT m.nome, j.titulo, j.ano FROM Membros m JOIN Membro_Desenvolvimento md ON (m.membro_id=md.membro_id) JOIN Jogos j ON (md.titulo=j.titulo)
-- Alguns membros que não estão registrados na equipe de pesquisa podem estar listados como autores de algum dos artigos
-- (isso inclui membros externos). Vamos ver quais membros são citados como autores dos artigos, retornando seu nome e tipo de membro
SELECT m.nome, m.tipo FROM Membros m WHERE membro_id IN (SELECT a.membro_id FROM Autoria_Artigo a)
-- Os cursos são uma parte muito importante do CEGI. Vamos listar todos os membros que já coordenaram ao menos uma vez um curso do CEGI
SELECT nome FROM Membros WHERE membro_id IN (SELECT membro_id FROM Responsavel_Curso) GROUP BY nome
-- Vamos listar todos os membros do CEGI e listar os seus cargos ativos, caso o membro possua algum cargo (membros externos não possuem)
SELECT m.nome, cm.cargo, cm.equipe FROM Membros m LEFT JOIN Cargo_Membro cm ON (m.membro_id=cm.membro_id) WHERE cm.dataFIM IS NULL
-- Nem todos os membros podem se responsabilizar por coisas importantes como o Processo Seletivo e os Cursos. Vamos listar todos os
-- membros que já carregaram essa responsabilidade e quantas vezes eles foram responsáveis por algo do tipo
SELECT m.nome, ((SELECT COUNT(*) FROM Responsavel_Curso rc WHERE m.membro_id=rc.membro_id) + (SELECT COUNT(*) FROM Responsavel_Processo_Seletivo rps WHERE m.membro_id=rps.membro_id)) as Participacoes FROM Membros m HAVING Participacoes > 0
-- Pode ser que, por algum motivo, seja necessário falar com alguém que fez parte da equipe de desenvolvimento de um determinado jogo.
-- Para tal, vamos retornar a lista de todos os jogos, com os membros com cargos ainda ativos dentro do projeto
SELECT j.titulo, m.nome, cm.cargo, cm.equipe FROM Jogos j LEFT JOIN Membro_Desenvolvimento md ON (j.titulo=md.titulo) LEFT JOIN Membros m ON (md.membro_id=m.membro_id) LEFT JOIN Cargo_Membro cm ON (md.membro_id=cm.membro_id) WHERE cm.dataFim IS NULL
-- Com o tempo, o projeto vem crescendo. Com isso, pode ser que o tamanho das equipes de desenvolvimento para cada jogo mude.
-- Com isso, vamos retornar o tamanho da equipe de desenvolvimento de cada um dos jogos
SELECT j.titulo, COUNT(md.membro_id) FROM Jogos j JOIN Membro_Desenvolvimento md ON (j.titulo=md.titulo) GROUP BY j.titulo
-- Qual dos cursos do CEGI é o mais famoso? Vamos descobrir, retornando o número total de participantes por curso
SELECT c.curso, ((SELECT COUNT(pec.email) FROM Participante_Externo_Curso pec WHERE c.curso=pec.curso) + (SELECT COUNT(pmc.membro_id) FROM Participante_Membro_Curso pmc WHERE c.curso=pmc.curso)) as alunos FROM Curso c GROUP BY c.curso
-- Quantos jogos será que cada membro fez parte do desenvolvimento? Vamos descobrir:
SELECT m.nome, COUNT(md.membro_id) FROM Membros m LEFT JOIN Membro_Desenvolvimento md ON (m.membro_id=md.membro_id) GROUP BY m.nome