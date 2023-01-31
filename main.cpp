#include <string>
#include <vector>
#include <iostream>
#include <aws/lambda-runtime/runtime.h>
#include <aws/core/utils/json/JsonSerializer.h>
#include <aws/core/utils/memory/stl/SimpleStringStream.h>

using namespace std;
using namespace aws::lambda_runtime;
using namespace Aws::Utils::Json;

#define NUM_INPUTS 16
#define NUM_OUTPUTS 11
#define ETA 0.1

vector<double> weights, answers, sums, results;

void init_weights() {
    weights.push_back(-2.99999);
    weights.push_back(1.40564);
    weights.push_back(-3.19807);
    weights.push_back(16.2081);
    weights.push_back(-3.79415);
    weights.push_back(-3.5952);
    weights.push_back(5.4035);
    weights.push_back(-3.79104);
    weights.push_back(-4.39177);
    weights.push_back(-1.39253);
    weights.push_back(-3.19826);
    weights.push_back(-1.59141);
    weights.push_back(3.60711);
    weights.push_back(-4.39486);
    weights.push_back(-4.39696);
    weights.push_back(4.80015);
    weights.push_back(-2.79909);
    weights.push_back(14.8036);
    weights.push_back(2.80147);
    weights.push_back(7.80166);
    weights.push_back(-11.5901);
    weights.push_back(-3.19554);
    weights.push_back(-5.79881);
    weights.push_back(-0.799953);
    weights.push_back(-6.79991);
    weights.push_back(-3.19622);
    weights.push_back(-4.19468);
    weights.push_back(3.80571);
    weights.push_back(-4.79398);
    weights.push_back(-8.59393);
    weights.push_back(1.20166);
    weights.push_back(-2.99337);
    weights.push_back(-3.79549);
    weights.push_back(0.203521);
    weights.push_back(-3.99943);
    weights.push_back(0.606077);
    weights.push_back(-3.79217);
    weights.push_back(-3.39197);
    weights.push_back(-2.1948);
    weights.push_back(-3.19698);
    weights.push_back(-0.79124);
    weights.push_back(20.8073);
    weights.push_back(-2.19044);
    weights.push_back(-1.59074);
    weights.push_back(-9.39461);
    weights.push_back(6.60142);
    weights.push_back(8.00462);
    weights.push_back(-3.99765);
    weights.push_back(-5.79138);
    weights.push_back(0.602096);
    weights.push_back(-3.1922);
    weights.push_back(0.208437);
    weights.push_back(-0.590032);
    weights.push_back(-0.590003);
    weights.push_back(0.00611499);
    weights.push_back(-1.79608);
    weights.push_back(-3.59734);
    weights.push_back(-2.39703);
    weights.push_back(-1.1916);
    weights.push_back(16.2002);
    weights.push_back(-8.99624);
    weights.push_back(-2.79907);
    weights.push_back(0.406772);
    weights.push_back(-4.99944);
    weights.push_back(1.60009);
    weights.push_back(0.0091879);
    weights.push_back(0.802759);
    weights.push_back(-0.597271);
    weights.push_back(-0.794121);
    weights.push_back(0.406912);
    weights.push_back(-2.19162);
    weights.push_back(-6.59274);
    weights.push_back(-3.79515);
    weights.push_back(-0.997946);
    weights.push_back(-2.99256);
    weights.push_back(-1.79532);
    weights.push_back(3.40458);
    weights.push_back(14.6095);
    weights.push_back(-4.19256);
    weights.push_back(-0.798917);
    weights.push_back(1.60599);
    weights.push_back(-0.196148);
    weights.push_back(1.20735);
    weights.push_back(0.20609);
    weights.push_back(0.00572405);
    weights.push_back(0.203613);
    weights.push_back(0.00151555);
    weights.push_back(-0.597749);
    weights.push_back(-2.99575);
    weights.push_back(2.80803);
    weights.push_back(3.20517);
    weights.push_back(4.4099);
    weights.push_back(-1.39248);
    weights.push_back(-4.59654);
    weights.push_back(0.20169);
    weights.push_back(11.2066);
    weights.push_back(-5.39508);
    weights.push_back(-5.59936);
    weights.push_back(-2.993);
    weights.push_back(-4.79495);
    weights.push_back(-11.1985);
    weights.push_back(-0.190504);
    weights.push_back(-0.198584);
    weights.push_back(-0.790949);
    weights.push_back(-5.99307);
    weights.push_back(-5.59697);
    weights.push_back(-2.79573);
    weights.push_back(1.6007);
    weights.push_back(-3.19033);
    weights.push_back(-0.993168);
    weights.push_back(-1.19847);
    weights.push_back(-1.59123);
    weights.push_back(4.00822);
    weights.push_back(-3.79418);
    weights.push_back(-1.99809);
    weights.push_back(-3.19822);
    weights.push_back(-4.39183);
    weights.push_back(23.4048);
    weights.push_back(-1.79844);
    weights.push_back(2.80504);
    weights.push_back(-7.59268);
    weights.push_back(4.80406);
    weights.push_back(1.6028);
    weights.push_back(-6.79431);
    weights.push_back(3.20682);
    weights.push_back(-2.79244);
    weights.push_back(-2.39278);
    weights.push_back(-3.79525);
    weights.push_back(2.40123);
    weights.push_back(4.40368);
    weights.push_back(16.8083);
    weights.push_back(-6.79965);
    weights.push_back(-9.59483);
    weights.push_back(-6.59337);
    weights.push_back(-1.99574);
    weights.push_back(-2.99895);
    weights.push_back(0.809493);
    weights.push_back(-0.390786);
    weights.push_back(0.205495);
    weights.push_back(3.60346);
    weights.push_back(-18.5953);
    weights.push_back(7.40375);
    weights.push_back(14.8085);
    weights.push_back(-5.19683);
    weights.push_back(4.00456);
    weights.push_back(-2.99728);
    weights.push_back(-2.79017);
    weights.push_back(-3.19702);
    weights.push_back(9.20739);
    weights.push_back(-8.59433);
    weights.push_back(-4.59804);
    weights.push_back(3.00761);
    weights.push_back(-8.39161);
    weights.push_back(-2.19602);
    weights.push_back(0.405009);
    weights.push_back(-5.5911);
    weights.push_back(-5.39973);
    weights.push_back(-0.590054);
    weights.push_back(-3.19427);
    weights.push_back(1.20051);
    weights.push_back(-3.39469);
    weights.push_back(-5.79806);
    weights.push_back(2.00843);
    weights.push_back(-0.793732);
    weights.push_back(9.80658);
    weights.push_back(0.201979);
    weights.push_back(17.6084);
    weights.push_back(-10.3988);
    weights.push_back(-1.7989);
    weights.push_back(-0.192569);
    weights.push_back(2.60314);
    weights.push_back(2.60941);
    weights.push_back(-3.79714);
    weights.push_back(-0.796637);
    weights.push_back(-15.1986);
    weights.push_back(1.40733);
    weights.push_back(8.20835);
    weights.push_back(-6.59292);
    weights.push_back(-3.994);
    weights.push_back(5.40747);
    weights.push_back(-1.19747);
    weights.push_back(-9.79856);
    weights.push_back(-4.59998);
    weights.push_back(-3.39939);
    weights.push_back(17.6081);
    weights.push_back(6.80853);
    weights.push_back(-10.9979);
}

void init_answers(string input) {
	// https://cplusplus.com/forum/beginner/212841/
	for (unsigned i = 0; i < input.size(); ++i) {
		answers.push_back(input[i] - '0');
	}
}

void calculate_sums() {
	double sum = 0;
	int	aux = 0;
	
	for(unsigned j = 0; j < NUM_OUTPUTS; j++) {
		for(unsigned i = 0; i < NUM_INPUTS + 1; i++) {
			sum = sum + answers[i] * weights[i + aux];
		}
		sums.push_back(sum);
		sum = 0;
		aux = aux + NUM_INPUTS + 1;
	}
}

int calculate_sgn() {
	int careerIndex = -1;
	for(unsigned i = 0; i < sums.size(); i++){
		if(sums[i] < 0) {
			results.push_back(-1);
		} else {
			results.push_back(1);
			careerIndex = i;
		}
	}
	return careerIndex;
}

int run_ann_dio_careers(string input) {
	answers.clear();
	weights.clear();
	sums.clear();
	results.clear();

	init_weights();
	init_answers(input);
	answers.push_back(1); // bias
	calculate_sums();
	return calculate_sgn();
}

int run_ann_alternative() {
    // Comeca atribuindo o i­ndice de maior valor ao "primeiro" elemento lido.
    int maxIndex = 0;
    int maxValue = answers[0];
    
    // Itera de i = 0 até i = 15 (atribuido acima)
    for (int i = 0; i < NUM_INPUTS; i++) {
        // No caso do valor do vetor ser maior na posicao i do que na posicao de maximo anterior, 
        // Substitui o i­ndice do maximo pelo i­ndice i e o valor do maximo pelo valor do vetor no i­ndice i.
        if (answers[i] > maxValue) {
            maxIndex = i;
            maxValue = answers[i];
        }
    }
    // Mapeia o indice com o valor máximo com sua respectiva Carreira:
    switch (maxIndex) {
        case 3:
        case 4:
            return 0;  // Back-end index
        case 0:
        case 1:
        case 2:
            return 1;  // Front-end index
        case 7:
            return 2;  // Mobile index
        case 8:
            return 3;  // Infra index
        case 9:
            return 4;  // Cloud index
        case 5:
        case 6:
        case 10:
            return 5;  // Data & Analytics index
        case 15:
            return 6;  // Games index
        case 11:
            return 7;  // QA index
        case 12:
            return 8;  // Web & IA index
        case 13:
            return 9;  // Lideranca index
        case 14:
            return 10; // CRM index
    }
    return -1;
}

invocation_response create_success_response(int careerIndex, string careerName, bool isAnn) {

    JsonValue career, resp;
    career.WithInteger("id", careerIndex + 1).WithString("name", careerName).WithBool("isAnn", isAnn);
    resp.WithInteger("status", 200).WithObject("career", career);

    return invocation_response::success(resp.View().WriteCompact(), "application/json");
}

invocation_response create_error_response(string message) {

    JsonValue resp;
    resp.WithInteger("status", 400).WithString("message", message);
    
    return invocation_response::success(resp.View().WriteCompact(), "application/json");
}

invocation_response dio_handler(invocation_request const& request) {

    JsonValue json(request.payload);
    if (!json.WasParseSuccessful()) {
        return invocation_response::failure("Failed to parse input JSON", "InvalidJSON");
    }

    auto v = json.View();

    if (v.ValueExists("body") && v.GetObject("body").IsString()) {
        auto body = v.GetString("body");
        JsonValue body_json(body);

        if (body_json.WasParseSuccessful()) {            
            auto body_v = body_json.View();
            bool hasInput = body_v.ValueExists("answers") && body_v.GetObject("answers").IsString();
            string careerSurveyAnswers = hasInput ? body_v.GetString("answers") : "";
            
            if (careerSurveyAnswers.size() == NUM_INPUTS) {
                bool isAnn = true;
                int careerIndex = run_ann_dio_careers(careerSurveyAnswers);
                cout << "[ANN_DIO_careerS]: '" << careerSurveyAnswers << "' => " << careerIndex;
                if (careerIndex == -1) {
                    careerIndex = run_ann_alternative();
                    isAnn = false;
                }
                string careerName;
                switch (careerIndex) {
                    case 0:
                        careerName = "Carreira Back-end";
                        break;
                    case 1:
                        careerName = "Carreira Front-end";
                        break;
                    case 2:
                        careerName = "Carreira Mobile";
                        break;
                    case 3:
                        careerName = "Carreira Infra, DevOps e Security";
                        break;
                    case 4:
                        careerName = "Carreira Cloud";
                        break;
                    case 5:
                        careerName = "Carreira Data e Analytics";
                        break;
                    case 6:
                        careerName = "Carreira Games";
                        break;
                    case 7:
                        careerName = "Carreira Qualidade de Software";
                        break;
                    case 8:
                        careerName = "Carreira Web3 e IA";
                        break;
                    case 9:
                        careerName = "Carreira Liderança e SoftSkill";
                        break;
                    case 10:
                        careerName = "Carreira CRM";
                        break;
                    default:
                        return create_error_response("Não identificamos uma carreira ideal pra você. Responda novamente deixando suas preferências mais claras 😉");
                }
                return create_success_response(careerIndex, careerName, isAnn);
            } else {
                Aws::SimpleStringStream ss;
                ss << "Número de entradas inválido, " << NUM_INPUTS << " posições são necessárias.";
                return create_error_response(ss.str());
            }
        }
    }
    return create_error_response("Requisição inválida, confira os dados enviados.");
}

int main() {
    run_handler(dio_handler);
    return 0;
}
