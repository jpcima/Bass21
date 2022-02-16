#include "Bass21Filters.h"

TF2d makePresence(double sampleRate, double param)
{
    TF2d analog;
    double *B = analog.b();
    double *A = analog.a();

    double R1 = 330e3;
    double C1 = 220e-12;
    double R2 = 3.3e3;
    double C2 = 10e-9;
    double Rp = 100e3*(1.0-param);

    B[0] = 1.0;
    B[1] = C2*(Rp+R2)+R1*C1+R1*C2;
    B[2] = R1*C1*(Rp+R2)*C2;
    A[0] = 1.0;
    A[1] = C2*(Rp+R2)+R1*C1;
    A[2] = R1*C1*(Rp+R2)*C2;

    return bilinearTransform2(analog, sampleRate, 1.0);
}

TF2d makeDrive(double sampleRate, double param)
{
    TF2d analog;
    double *B = analog.b();
    double *A = analog.a();

    double R1 = 330e3;
    double C1 = 220e-12;
    double R2 = 3.3e3;
    double Rp = 100e3*(1.0-param);

    B[0] = R1+R2+Rp;
    B[1] = C1*R1*(R2+Rp);
    B[2] = 0.0;
    A[0] = R2+Rp;
    A[1] = C1*R1*(R2+Rp);
    A[2] = 0.0;

    return bilinearTransform2(analog, sampleRate, 1.0);
}

TF3d makeRCNetwork1(double sampleRate)
{
    TF3d analog;
    double *B = analog.b();
    double *A = analog.a();

    double R1 = 100e3;
    double R2 = 2.2e3;
    double R3 = 22e3;
    double C1 = 22e-9;
    double C2 = 22e-9;
    double C3 = 22e-9;

    B[0] = 1.0;
    B[1] = C1*R2+C2*R3+C3*R3+C3*R2;
    B[2] = C2*C1*R2*R3+C3*C1*R2*R3+C3*C2*R2*R3;
    B[3] = C3*C2*C1*R1*R2*R3;
    A[0] = 1.0;
    A[1] = C1*R2+C2*R3+C2*R1+C3*R3+C3*R2;
    A[2] = C2*C1*R2*R3+C2*C1*R1*R2+C3*C1*R2*R3+C3*C2*R2*R3+C3*C2*R1*R3+C3*C2*R1*R2;
    A[3] = C3*C2*C1*R1*R2*R3;

    return bilinearTransform3(analog, sampleRate, 1.0);
}

TF2d makeRCNetwork2(double sampleRate)
{
    TF2d analog;
    double *B = analog.b();
    double *A = analog.a();

    double R1 = 22e3;
    double R2 = 6.2e3;
    double C1 = 22e-9;
    double C2 = 47e-9;

    B[0] = 1.0;
    B[1] = C1*R2+C2*R2;
    B[2] = C2*C1*R1*R2;
    A[0] = 1.0;
    A[1] = C1*R2+C2*R2+C2*R1;
    A[2] = C2*C1*R1*R2;

    return bilinearTransform2(analog, sampleRate, 1.0);
}

TF3d makeCamelFilter(double sampleRate)
{
    TF3d analog;
    double *B = analog.b();
    double *A = analog.a();

    double R1 = 10e3;
    double R2 = 22e3;
    double R3 = 22e3;
    double R4 = 22e3;
    double R5 = 10e3;
    double C1 = 47e-9;
    double C2 = 470e-12;
    double C3 = 10e-9;

    B[0] = R4;
    B[1] = C1*R4*R5;
    B[2] = 0.0;
    B[3] = 0.0;
    A[0] = R4+R1;
    A[1] = C1*R4*R5+C1*R2*R4+C1*R1*R5+C1*R1*R4+C1*R1*R2+C2*R3*R4+C2*R2*R4+C2*R1*R4+C2*R1*R3+C2*R1*R2;
    A[2] = C2*C1*R3*R4*R5+C2*C1*R2*R4*R5+C2*C1*R2*R3*R4+C2*C1*R1*R4*R5+C2*C1*R1*R3*R5+C2*C1*R1*R3*R4+C2*C1*R1*R2*R5+C2*C1*R1*R2*R3+C3*C2*R2*R3*R4+C3*C2*R1*R3*R4+C3*C2*R1*R2*R3;
    A[3] = C3*C2*C1*R2*R3*R4*R5+C3*C2*C1*R1*R3*R4*R5+C3*C2*C1*R1*R2*R3*R5;

    return bilinearTransform3(analog, sampleRate, 1.0);
}

TF6d makeEQ(double sampleRate, double bass, double treble)
{
    TF6d analog;
    double *B = analog.b();
    double *A = analog.a();

    //formula refers to control values inverted
    bass = 1.0-bass;
    treble = 1.0-treble;

    B[0] =
      0.0;
    B[1] =
      (10000.0)*bass - (11000.0);
    B[2] =
      ((4722366482869644988655.0/147573952589676412928.0)*(bass*bass))
      - ((3149228148263694434375.0/147573952589676412928.0)*bass)
      - (598633738680022361533287.0/36893488147419103232000.0);
    B[3] = 0.0
         - ((1.0/100.0)*(bass*bass)*treble)
         + ((95513923305516444051222397770391.0/2028240960365167042394725128601600.0)*(bass*bass))
         - ((1.0/100.0)*bass*(treble*treble))
         + ((1.0/50.0)*bass*treble)
         - ((11855575473574492365904017309744059.0/253530120045645880299340641075200000.0)*bass)
         + ((11.0/1000.0)*(treble*treble))
         - ((87.0/10000.0)*treble)
         - (14370594264427299590777634582379451.0/2535301200456458802993406410752000000.0);
    B[4] = 0.0
         - ((7486212072260646522045135498046875.0/340282366920938463463374607431768211456.0)*(bass*bass)*(treble*treble))
         + ((4491727243356387913227081298828125.0/340282366920938463463374607431768211456.0)*(bass*bass)*treble)
         + ((43930290233957032614896735927734375.0/2722258935367507707706996859454145691648.0)*(bass*bass))
         + ((7486212072260646522045135498046875.0/340282366920938463463374607431768211456.0)*bass*(treble*treble))
         - ((4491727243356387913227081298828125.0/340282366920938463463374607431768211456.0)*bass*treble)
         - ((43930290233957032614896735927734375.0/2722258935367507707706996859454145691648.0)*bass)
         + ((1497242414452129304409027099609375.0/680564733841876926926749214863536422912.0)*(treble*treble))
         - ((2096139380232981026172637939453125.0/1361129467683753853853498429727072845824.0)*treble)
         - (3988653792100472466945648193359375.0/5444517870735015415413993718908291383296.0);
    B[5] =
      ((55263030661574758589267730712890625.0/11417981541647679048466287755595961091061972992.0)*bass*(bass - (1.0))*(0.0 - (1000.0)*(treble*treble) + (700.0)*treble + (333.0)));
    B[6] =
      0.0;
    A[0] =
      (1120000.0) - (100000.0)*bass;
    A[1] =
      ((827159382962765777100875.0/73786976294838206464.0)*bass)
      - ((97398808709186431407275.0/73786976294838206464.0)*(bass*bass))
      + (22486138303994174387839511.0/3689348814741910323200.0);
    A[2] =
      ((1.0/10.0)*(bass*bass)*treble)
      - ((554005154673064069875538171729.0/12379400392853802748991242240.0)*(bass*bass))
      + ((1.0/10.0)*bass*(treble*treble))
      - ((11.0/5.0)*bass*treble)
      + ((11172233007643856170213158767360603.0/198070406285660843983859875840000.0)*bass)
      - ((28.0/25.0)*(treble*treble))
      + ((2097.0/1000.0)*treble)
      + (4803318945294176732167021742106863.0/495176015714152109959649689600000.0);
    A[3] =
      ((395912635463280607188582045966881.0/324518553658426726783156020576256000.0)*(bass*bass)*(treble*treble))
      - ((924536224793224579754221815612658771.0/83076749736557242056487941267521536000.0)*(bass*bass)*treble)
      - ((507040844370222621749497226472328135711.0/10384593717069655257060992658440192000000.0)*(bass*bass))
      - ((931846978770041617107737440612658771.0/83076749736557242056487941267521536000.0)*bass*(treble*treble))
      + ((877514784442333180710841126228898003.0/41538374868278621028243970633760768000.0)*bass*treble)
      + ((4083733035316798552790018918194514614443.0/83076749736557242056487941267521536000000.0)*bass)
      - ((3611720156421957836512892203189315491.0/1038459371706965525706099265844019200000.0)*(treble*treble))
      + ((47940277510652695890303360485452680333.0/8307674973655724205648794126752153600000.0)*treble)
      + (1936978606034868499295094264265095385289.0/519229685853482762853049632922009600000000.0);
    A[4] =
      ((38827074815011218430459499359130859375.0/1393796574908163946345982392040522594123776.0)*(bass*bass)*(treble*treble))
      - ((51068199162681861845266819000244140625.0/1393796574908163946345982392040522594123776.0)*(bass*bass)*treble)
      - ((99107653864029446716585253626748046875.0/11150372599265311570767859136324180752990208.0)*(bass*bass))
      - ((38827074815011218430459499359130859375.0/1393796574908163946345982392040522594123776.0)*bass*(treble*treble))
      + ((51068199162681861845266819000244140625.0/1393796574908163946345982392040522594123776.0)*bass*treble)
      + ((99107653864029446716585253626748046875.0/11150372599265311570767859136324180752990208.0)*bass)
      - ((1585472873686109630191326141357421875.0/696898287454081973172991196020261297061888.0)*(treble*treble))
      + ((16362191671670370027673244476318359375.0/5575186299632655785383929568162090376495104.0)*treble)
      + (54095420370500304200094670353834375.0/696898287454081973172991196020261297061888.0);
    A[5] =
      ((1833247147700098857916891574859619140625.0/365375409332725729550921208179070754913983135744.0)*(bass*bass)*(treble*treble))
      - ((9454388675080322685949504375457763671875.0/1461501637330902918203684832716283019655932542976.0)*(bass*bass)*treble)
      - ((500354302003399815320782081071474609375.0/2923003274661805836407369665432566039311865085952.0)*(bass*bass))
      - ((1833247147700098857916891574859619140625.0/365375409332725729550921208179070754913983135744.0)*bass*(treble*treble))
      + ((9454388675080322685949504375457763671875.0/1461501637330902918203684832716283019655932542976.0)*bass*treble)
      + ((500354302003399815320782081071474609375.0/2923003274661805836407369665432566039311865085952.0)*bass)
      - ((3183150566106706671416759490966796875.0/1461501637330902918203684832716283019655932542976.0)*(treble*treble))
      + ((3183150566106706671416759490966796875.0/1461501637330902918203684832716283019655932542976.0)*treble)
      + (840351749452170561254024505615234375.0/11692013098647223345629478661730264157247460343808.0);
    A[6] = 0.0
      -((117489690137807889841496944427490234375.0/24519928653854221733733552434404946937899825954937634816.0)*bass*(bass - (1.0))*(0.0 - (1000.0)*(treble*treble) + (1000.0)*treble + (33.0)));

  return bilinearTransform6(analog, sampleRate, 1.0);
}

//------------------------------------------------------------------------------
static FilterCache::Ptr computeFilterCache(uint32_t sampleRate)
{
    FilterCache::Ptr fc{new FilterCache};

    constexpr uint32_t size = 128;

    for (uint32_t i = 0; i < size; ++i) {
        double param = i / (double)(size - 1);
        fc->presence[i] = makePresence(sampleRate, param).to<float>();
    }

    for (uint32_t i = 0; i < size; ++i) {
        double param = i / (double)(size - 1);
        fc->drive[i] = makeDrive(sampleRate, param).to<float>();
    }

    fc->rcNetwork1 = makeRCNetwork1(sampleRate).to<float>();
    fc->rcNetwork2 = makeRCNetwork2(sampleRate).to<float>();
    fc->camelFilter = makeCamelFilter(sampleRate).to<float>();

    for (uint32_t ib = 0; ib < size; ++ib) {
        double bass = ib / (double)(size - 1);
        for (uint32_t it = 0; it < size; ++it) {
            double treble = it / (double)(size - 1);
            fc->eq[ib][it] = makeEQ(sampleRate, bass, treble).to<float>();
        }
    }

    return fc;
}

//------------------------------------------------------------------------------
#include <map>
#include <mutex>

static std::map<uint32_t, FilterCache::Ptr> globalFilterCache;
static std::mutex globalFilterCacheMutex;

FilterCache::Ptr getFilterCache(uint32_t sampleRate)
{
    std::unique_lock<std::mutex> lock{globalFilterCacheMutex};

    auto it = globalFilterCache.find(sampleRate);
    if (it != globalFilterCache.end())
        return it->second;

    lock.unlock();
    FilterCache::Ptr fc = computeFilterCache(sampleRate);
    lock.lock();

    return globalFilterCache.insert(std::make_pair(sampleRate, fc)).first->second;
}

//------------------------------------------------------------------------------
std::ostream &operator<<(std::ostream &os, const FilterCache &fc)
{
    constexpr uint32_t size = 128;

    for (uint32_t i = 0; i < size; ++i) {
        double param = i / (double)(size - 1);
        os << "*** Presence [param=" << param << "]\n" << fc.presence[i] << "\n";
    }

    for (uint32_t i = 0; i < size; ++i) {
        double param = i / (double)(size - 1);
        os << "*** Drive [param=" << param << "]\n" << fc.drive[i] << "\n";
    }

    os << "*** RC Network 1\n" << fc.rcNetwork1 << "\n";
    os << "*** RC Network 2\n" << fc.rcNetwork2 << "\n";
    os << "*** Camel filter\n" << fc.camelFilter << "\n";

    for (uint32_t ib = 0; ib < size; ++ib) {
        double bass = ib / (double)(size - 1);
        for (uint32_t it = 0; it < size; ++it) {
            double treble = it / (double)(size - 1);
            os << "*** EQ [bass=" << bass << "; treble=" << treble << "]\n"
               << fc.eq[ib][it] << "\n";
        }
    }

    return os;
}
