from django.shortcuts import render
from .models import Cargo_Membro

def cargo_view(request):
    dados = Cargo_Membro.objects.all()
    return render(request, 'cargo.html', {'dados': dados})