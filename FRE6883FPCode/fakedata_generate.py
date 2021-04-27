from random import randint, uniform

def gen_stock_name():
    name_len = randint(3, 4)
    name_lst = [chr(randint(65, 90)) for _ in range(name_len)]
    name = ''.join(name_lst)
    return name

def gen_est_earnings():
    return uniform(0, 20)

def gen_rpt_earnings(est):
    return uniform(0.5, 1.5) * est

stock_map = dict()
num_of_stocks = 10

while len(stock_map) < num_of_stocks:
    stock_name = gen_stock_name()

    if stock_name in stock_map:
        continue

    est_earnings = gen_est_earnings()
    rpt_earnings = gen_rpt_earnings(est_earnings)
    surprise = rpt_earnings - est_earnings
    surprise_pct = surprise / est_earnings * 100

    stock_map[stock_name] = (
        stock_name,
        '29-OCT-20',
        'Sep 2020',
        round(est_earnings, 2),
        round(rpt_earnings, 2),
        round(surprise, 2),
        round(surprise_pct, 2)
    )

stocks = list(stock_map.values())
# stocks.sort(key=lambda s: s[-1])

with open('ZacksData.csv', 'w') as f:
    f.write("Symbol,EarningsAmntDate,PeriodEnding,EstEarnings,RptEarnings,Surprise,SurprisePct\n")
    for s in stocks:
        record = "{},{},{},{},{},{},{}\n".format(*s)
        f.write(record)
