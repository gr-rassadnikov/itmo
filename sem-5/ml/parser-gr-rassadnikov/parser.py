import csv
from typing import Optional
import requests as rq
from bs4 import BeautifulSoup


class CarDriverAttributes:
    def __init__(self,
                 oil: Optional[str],
                 transmission: Optional[str],
                 actuator: Optional[str]
                 ):
        self.oil = oil
        self.transmission = transmission
        self.actuator = actuator


class CarInfo:
    def __init__(self,
                 attributes: CarDriverAttributes,
                 price: Optional[int]
                 ):
        self.attributes = attributes
        self.price = price


class CarDetailInfo:
    def __init__(self,
                 rating: Optional[float],
                 engine_capacity: Optional[float]
                 ):
        self.rating = rating
        self.engine_capacity = engine_capacity


class CarModel:
    def __init__(self,
                 name: Optional[str],
                 year: Optional[str]
                 ):
        self.name = name
        self.year = year


class Car:
    def __init__(self,
                 model: CarModel,
                 info: CarInfo,
                 detail_info: CarDetailInfo
                 ):
        self.model = model
        self.info = info
        self.detail_info = detail_info

    def to_row(self):
        return {"name": model.name,
                "year": model.year,
                "price": info.price,
                "rating": detail_info.rating,
                "oil": info.attributes.oil,
                "actuator": info.attributes.actuator,
                "transmission": info.attributes.transmission,
                "engine_capacity": detail_info.engine_capacity
                }


def get_price(soup: BeautifulSoup) -> Optional[int]:
    try:
        price = soup.find('span', attrs={'data-ftid': 'bull_price'}).text
        return int(price.replace(" ", ""))
    except AttributeError:
        return None
    except ValueError:
        return None


def get_rating(soup: BeautifulSoup) -> Optional[float]:
    try:
        score_text = soup.find('div', attrs={'data-ftid': 'component_rating'}).text
        rating = score_text[16:]
        return float(rating)
    except IndexError:
        return None
    except AttributeError:
        return None
    except ValueError:
        return None


def get_engine_capacity(soup: BeautifulSoup) -> Optional[float]:
    try:
        engine_capacity_text = soup.find('span', attrs={'class': 'css-1jygg09 e162wx9x0'}).text
        engine_capacity = engine_capacity_text[-6:-2]
        return float(engine_capacity)
    except IndexError:
        return None
    except AttributeError:
        return None
    except ValueError:
        return None


def parse_detail_page(link: str) -> CarDetailInfo:
    resp = rq.get(f'{link}')
    soup = BeautifulSoup(resp.text, 'lxml')

    rating = get_rating(soup)
    engine_capacity = get_engine_capacity(soup)

    return CarDetailInfo(rating, engine_capacity)


def get_attribute_by_index(car_attributes, index: int) -> Optional[str]:
    try:
        return car_attributes[index].text[:-1]
    except IndexError:
        return None


def get_CarDriverAttributes(soup: BeautifulSoup) -> CarDriverAttributes:
    try:
        car_attributes = soup.find_all('span', attrs={'data-ftid': 'bull_description-item'})
        oil = get_attribute_by_index(car_attributes, 1)
        kpp = get_attribute_by_index(car_attributes, 1)
        actuator = get_attribute_by_index(car_attributes, 1)
        return CarDriverAttributes(oil, kpp, actuator)
    except AttributeError:
        return CarDriverAttributes(None, None, None)


def parse_title(car) -> CarModel:
    car_title = car.find('span', attrs={'data-ftid': 'bull_title'}).text
    data = car_title.split(', ')
    name = data[0]
    year = data[1]

    return CarModel(name, year)


def parse_item(car) -> CarInfo:
    attributes = get_CarDriverAttributes(car)
    price = get_price(car)

    return CarInfo(attributes, price)


if __name__ == '__main__':
    with open('data.csv', 'w') as csvfile:
        fields = ['name',
                  'year',
                  "price",
                  "rating",
                  "oil",
                  "actuator",
                  "transmission",
                  "engine_capacity"]

        writer = csv.DictWriter(csvfile, fieldnames=fields)
        writer.writeheader()

        start_page = 1
        end_page = 100

        for page in range(start_page, end_page):
            print(page)
            resp = rq.get(f'https://spb.drom.ru/auto/all/page{page}/')
            soup = BeautifulSoup(resp.text, 'lxml')
            cars = soup.find_all('a', attrs={'data-ftid': 'bulls-list_bull'})
            for car in cars:
                detail_link = car.get('href')
                info = parse_item(car)
                detail_info = parse_detail_page(detail_link)
                model = parse_title(car)

                car = Car(model, info, detail_info)

                writer.writerow(car.to_row())
