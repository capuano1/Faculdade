from django.db import models

class Cargo_Membro(models.Model):
    membro_id = models.IntegerField(primary_key=True)
    cargo = models.CharField(max_length=50)
    equipe = models.CharField(max_length=20)
    dataIni = models.DateField()
    dataFim = models.DateField()

    class Meta:
        db_table = 'Cargo_Membro'
        managed = False
        unique_together = (('membro_id', 'cargo', 'equipe'),)