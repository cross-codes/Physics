import random

NUM_NEUTRONS = 10000
ENERGY_THRESHOLD = 0.7
MAX_ENERGY = 2.0

SCATTERING_THRESHOLD = 1.0

def russian_roulette(energy):
    if energy > SCATTERING_THRESHOLD:
        # High-energy neutrons have a lower chance of survival (more likely to scatter)
        prob = 0.05
    else:
        # Low-energy neutrons have a higher chance of absorption
        prob = 0.1
    return random.random() < prob

def run_simulation():
    surviving_neutrons = 0

    for _ in range(NUM_NEUTRONS):
        energy = random.uniform(0.1, MAX_ENERGY)
        alive = True

        if energy < ENERGY_THRESHOLD:
            alive = False
        else:
            energy *= random.uniform(0.5, 1.0)

        if alive and russian_roulette(energy):
            alive = False

        if alive:
            surviving_neutrons += 1

    return surviving_neutrons

surviving_neutrons = run_simulation()
print(f"Surviving neutrons: {surviving_neutrons} out of {NUM_NEUTRONS}")
