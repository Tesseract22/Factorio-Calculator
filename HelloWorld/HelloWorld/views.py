from django.http import HttpResponse
from django.shortcuts import render


def hello(request):
    return HttpResponse("Hello World !")



def tmp(request):
    context = {}
    context['text'] = 'Factorio'
    li = ["tom", "bob", "Elen"]
    context["li"] = li
    
    return render(request, 'child.html', context)