from collections import namedtuple

price_split = namedtuple('price_split', ['couple', 'singleton'])

def split(total_price, total_sqft, room1_sqft, room2_sqft, couple_occupies=1):
    '''
    Returns a tuple representing the total price each person pays
    Total square feet is total internal square feet + oustdoor square feet (balconies/patios)
    A room's square feet is equal to:
    the room sqft + closet sqft + attached/assigned bathroom sqft + attached balcony/patio
    '''
    common_sqft = total_sqft - (room1_sqft + room2_sqft)

    common_area_value = total_price * common_sqft/total_sqft
    room1_value = total_price * room1_sqft/total_sqft
    room2_value = total_price * room2_sqft/total_sqft

    common_area_split = common_area_value / 3
    couple_owes = common_area_split * 2
    if couple_occupies == 1:
        people_owe = price_split(
                couple = room1_value + couple_owes,
                singleton = room2_value + common_area_split)
    else:
        people_owe = price_split(
                couple = room2_value + couple_owes,
                singleton = room1_value + common_area_split)

    return people_owe
