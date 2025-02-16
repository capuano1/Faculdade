from django.urls import path
from . import views

urlpatterns = [
    path('', views.cargo_view, name='cargo')
]