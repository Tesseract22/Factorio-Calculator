
import os

from django.http import HttpResponse
from django.shortcuts import render
from subprocess import Popen, PIPE
import csv



items = ['speed-module', 'advanced-circuit', 'electronic-circuit', 'speed-module-2', 'processing-unit', 'speed-module-3', 'productivity-module', 'productivity-module-2', 'productivity-module-3', 'effectivity-module', 'effectivity-module-2', 'effectivity-module-3', 'stack-inserter', 'iron-gear-wheel', 'fast-inserter', 'stack-filter-inserter', 'petroleum-gas', 'crude-oil', 'heavy-oil', 'light-oil', 'water', 'coal', 'steam', 'sulfuric-acid', 'sulfur', 'iron-plate', 'plastic-bar', 'solid-fuel', 'lubricant', 'empty-barrel', 'steel-plate', 'night-vision-equipment', 'belt-immunity-equipment', 'energy-shield-equipment', 'energy-shield-mk2-equipment', 'low-density-structure', 'battery-equipment', 'battery', 'battery-mk2-equipment', 'solar-panel-equipment', 'solar-panel', 'fusion-reactor-equipment', 'personal-laser-defense-equipment', 'laser-turret', 'discharge-defense-equipment', 'discharge-defense-remote', 'exoskeleton-equipment', 'electric-engine-unit', 'personal-roboport-equipment', 'personal-roboport-mk2-equipment', 'flamethrower-turret', 'pipe', 'engine-unit', 'artillery-turret', 'concrete', 'artillery-targeting-remote', 'radar', 'gun-turret', 'copper-plate', 'wooden-chest', 'wood', 'iron-stick', 'stone-furnace', 'stone', 'boiler', 'steam-engine', 'copper-cable', 'transport-belt', 'electric-mining-drill', 'burner-mining-drill', 'inserter', 'filter-inserter', 'long-handed-inserter', 'burner-inserter', 'offshore-pump', 'small-electric-pole', 'pistol', 'submachine-gun', 'firearm-magazine', 'light-armor', 'small-lamp', 'pipe-to-ground', 'assembling-machine-1', 'repair-pack', 'automation-science-pack', 'logistic-science-pack', 'lab', 'stone-wall', 'stone-brick', 'assembling-machine-2', 'splitter', 'underground-belt', 'loader', 'car', 'iron-chest', 'big-electric-pole', 'medium-electric-pole', 'shotgun', 'shotgun-shell', 'piercing-rounds-magazine', 'grenade', 'steel-furnace', 'gate', 'heavy-armor', 'steel-chest', 'fast-underground-belt', 'fast-splitter', 'iron-ore', 'hazard-concrete', 'refined-concrete', 'refined-hazard-concrete', 'landfill', 'fast-transport-belt', 'rail', 'locomotive', 'cargo-wagon', 'rail-signal', 'rail-chain-signal', 'train-stop', 'copper-ore', 'arithmetic-combinator', 'decider-combinator', 'constant-combinator', 'power-switch', 'programmable-speaker', 'red-wire', 'green-wire', 'poison-capsule', 'slowdown-capsule', 'cluster-grenade', 'explosives', 'defender-capsule', 'distractor-capsule', 'destroyer-capsule', 'cliff-explosives', 'uranium-rounds-magazine', 'uranium-238', 'rocket', 'explosive-rocket', 'atomic-bomb', 'rocket-control-unit', 'uranium-235', 'piercing-shotgun-shell', 'cannon-shell', 'explosive-cannon-shell', 'uranium-cannon-shell', 'explosive-uranium-cannon-shell', 'artillery-shell', 'flamethrower-ammo', 'express-transport-belt', 'assembling-machine-3', 'tank', 'spidertron', 'rocket-launcher', 'raw-fish', 'spidertron-remote', 'fluid-wagon', 'storage-tank', 'artillery-wagon', 'modular-armor', 'power-armor', 'power-armor-mk2', 'flamethrower', 'land-mine', 'combat-shotgun', 'chemical-science-pack', 'military-science-pack', 'production-science-pack', 'electric-furnace', 'utility-science-pack', 'flying-robot-frame', 'express-underground-belt', 'fast-loader', 'express-loader', 'express-splitter', 'logistic-robot', 'construction-robot', 'logistic-chest-passive-provider', 'logistic-chest-active-provider', 'logistic-chest-storage', 'logistic-chest-buffer', 'logistic-chest-requester', 'rocket-silo', 'roboport', 'substation', 'accumulator', 'beacon', 'pumpjack', 'oil-refinery', 'pump', 'chemical-plant', 'rocket-fuel', 'rocket-part', 'satellite', 'electric-energy-interface', 'nuclear-reactor', 'centrifuge', 'uranium-ore', 'nuclear-fuel', 'used-up-uranium-fuel-cell', 'uranium-fuel-cell', 'heat-exchanger', 'heat-pipe', 'steam-turbine']

def search_form(request):
    return render(request, 'search_form.html')



def search_calculate(request):
    ctx = {}
    ctx['items'] = items
    if request.POST:
        item_name = request.POST['item_name']
        amount = request.POST['amount']
        try:
            res = calculate(item_name, amount)
        except KeyError:
            ctx['error'] = "No Item named %s"%item_name
            return render(request, 'search_form.html', ctx)
        if 'display_but' in request.POST:
            ctx['res_csv'] = res
            ctx['item_name'] = item_name
            ctx['amount'] = amount
            return render(request, 'search_form.html', ctx)
        if 'download_but' in request.POST:  
            return download_csv(res, request.POST['item_name'] + ".csv")
    return render(request, 'search_form.html', ctx)

def download_csv(csvfile, filename):
    response = HttpResponse(
        content = "text/csv",   
        headers = {'Content-Disposition': 'attachment; filename="%s"'%filename}
    )
    writer = csv.writer(response)
    writer.writerows(csvfile)
    return response


def calculate(item, amount):
    cwd = os.getcwd()
    os.chdir(r"C:\Users\caleb\HelloWorld\Calculator")

    p = Popen([r'bin\socket.exe'], shell=True, stdout=PIPE, stdin=PIPE,)
    
    item = item + '\n'
    item = bytes(item, 'UTF-8')
    p.stdin.write(item)
    p.stdin.flush()

    amount = amount + '\n'
    amount = bytes(amount, 'UTF-8')
    p.stdin.write(amount)
    p.stdin.flush()
    
    os.chdir(cwd)
    lines = p.stdout.readlines()
    if lines == []:
        raise KeyError
    res = []
    for l in lines:
        res.append(l[:-1].decode("utf-8"))
    reader = csv.reader(res, delimiter=',')
    return reader