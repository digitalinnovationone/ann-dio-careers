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
	weights.push_back(-1.19999);
	weights.push_back(-2.59436);
	weights.push_back(-3.59807);
	weights.push_back(3.20809);
	weights.push_back(4.20585);
	weights.push_back(-0.795201);
	weights.push_back(-0.996497);
	weights.push_back(-2.19104);
	weights.push_back(-2.39177);
	weights.push_back(-1.19253);
	weights.push_back(-2.39826);
	weights.push_back(-0.391411);
	weights.push_back(1.80711);
	weights.push_back(-1.79486);
	weights.push_back(1.40304);
	weights.push_back(-0.99985);
	weights.push_back(0.400914);
	weights.push_back(1.00364);
	weights.push_back(2.00147);
	weights.push_back(1.60166);
	weights.push_back(-0.590115);
	weights.push_back(-0.795543);
	weights.push_back(-1.19881);
	weights.push_back(4.66933e-005);
	weights.push_back(-0.399911);
	weights.push_back(-0.396221);
	weights.push_back(-0.594683);
	weights.push_back(1.00571);
	weights.push_back(-0.593982);
	weights.push_back(-2.39393);
	weights.push_back(-0.198338);
	weights.push_back(-1.99337);
	weights.push_back(-0.995492);
	weights.push_back(0.00352123);
	weights.push_back(-1.79943);
	weights.push_back(-0.193923);
	weights.push_back(1.00783);
	weights.push_back(-2.59197);
	weights.push_back(-0.394801);
	weights.push_back(-4.39698);
	weights.push_back(-2.79124);
	weights.push_back(7.60727);
	weights.push_back(-2.59044);
	weights.push_back(0.409257);
	weights.push_back(-5.79461);
	weights.push_back(1.20142);
	weights.push_back(5.40462);
	weights.push_back(-2.79765);
	weights.push_back(-3.99138);
	weights.push_back(-2.3979);
	weights.push_back(-0.792203);
	weights.push_back(-1.59156);
	weights.push_back(-1.79003);
	weights.push_back(-2.19);
	weights.push_back(2.40611);
	weights.push_back(-0.796076);
	weights.push_back(-1.39734);
	weights.push_back(-2.59703);
	weights.push_back(-0.391599);
	weights.push_back(7.40024);
	weights.push_back(-0.196241);
	weights.push_back(-3.39907);
	weights.push_back(-0.993228);
	weights.push_back(-4.99944);
	weights.push_back(1.80009);
	weights.push_back(-0.590812);
	weights.push_back(-1.19724);
	weights.push_back(-0.197271);
	weights.push_back(-0.594121);
	weights.push_back(-0.193088);
	weights.push_back(-0.391624);
	weights.push_back(-2.59274);
	weights.push_back(-3.39515);
	weights.push_back(-1.19795);
	weights.push_back(-2.39256);
	weights.push_back(-0.395315);
	weights.push_back(2.40458);
	weights.push_back(2.20949);
	weights.push_back(0.407444);
	weights.push_back(-0.198917);
	weights.push_back(1.40599);
	weights.push_back(-0.196148);
	weights.push_back(1.00735);
	weights.push_back(-0.79391);
	weights.push_back(-0.194276);
	weights.push_back(-1.19639);
	weights.push_back(-1.79848);
	weights.push_back(-0.197749);
	weights.push_back(-0.395748);
	weights.push_back(0.608029);
	weights.push_back(1.20517);
	weights.push_back(2.6099);
	weights.push_back(-1.19248);
	weights.push_back(-0.796544);
	weights.push_back(0.20169);
	weights.push_back(2.40657);
	weights.push_back(0.404919);
	weights.push_back(-1.79936);
	weights.push_back(-0.193002);
	weights.push_back(-1.99495);
	weights.push_back(-2.99853);
	weights.push_back(-0.190504);
	weights.push_back(0.601416);
	weights.push_back(1.20905);
	weights.push_back(-1.39307);
	weights.push_back(-2.19697);
	weights.push_back(1.00427);
	weights.push_back(-0.599296);
	weights.push_back(-1.99033);
	weights.push_back(0.606832);
	weights.push_back(-1.99847);
	weights.push_back(-1.19123);
	weights.push_back(0.208217);
	weights.push_back(-1.59418);
	weights.push_back(-0.198086);
	weights.push_back(-0.798221);
	weights.push_back(-2.79183);
	weights.push_back(4.20475);
	weights.push_back(-0.198444);
	weights.push_back(-0.194961);
	weights.push_back(-4.79268);
	weights.push_back(5.00406);
	weights.push_back(4.0028);
	weights.push_back(-2.59431);
	weights.push_back(-0.593178);
	weights.push_back(-6.39244);
	weights.push_back(-1.79278);
	weights.push_back(-1.99525);
	weights.push_back(-3.99877);
	weights.push_back(0.203678);
	weights.push_back(4.40835);
	weights.push_back(-0.799649);
	weights.push_back(-3.19483);
	weights.push_back(-1.59337);
	weights.push_back(-0.795738);
	weights.push_back(-0.598953);
	weights.push_back(-1.59051);
	weights.push_back(-1.39079);
	weights.push_back(-0.994505);
	weights.push_back(-0.99654);
	weights.push_back(-1.79528);
	weights.push_back(2.40375);
	weights.push_back(1.60847);
	weights.push_back(0.803169);
	weights.push_back(3.20456);
	weights.push_back(-0.397281);
	weights.push_back(-0.99017);
	weights.push_back(-3.59702);
	weights.push_back(2.20739);
	weights.push_back(-2.59433);
	weights.push_back(-1.59804);
	weights.push_back(-0.992387);
	weights.push_back(-0.591606);
	weights.push_back(-2.99602);
	weights.push_back(-0.594991);
	weights.push_back(-3.7911);
	weights.push_back(-6.19973);
	weights.push_back(-1.99005);
	weights.push_back(-2.79427);
	weights.push_back(3.20051);
	weights.push_back(-0.594687);
	weights.push_back(-5.59806);
	weights.push_back(-1.39157);
	weights.push_back(-0.193732);
	weights.push_back(4.60658);
	weights.push_back(-1.79802);
	weights.push_back(6.60842);
	weights.push_back(2.60123);
	weights.push_back(-0.798901);
	weights.push_back(-0.592569);
	weights.push_back(0.00314066);
	weights.push_back(1.60941);
	weights.push_back(-0.797139);
	weights.push_back(-0.396637);
	weights.push_back(-6.3986);
	weights.push_back(0.407331);
	weights.push_back(0.808346);
	weights.push_back(-3.59292);
	weights.push_back(-0.793998);
	weights.push_back(0.607472);
	weights.push_back(-3.39747);
	weights.push_back(-1.39856);
	weights.push_back(0.200016);
	weights.push_back(0.000610065);
	weights.push_back(4.40806);
	weights.push_back(2.40853);
	weights.push_back(-0.797894);
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
	int carrerIndex = -1;
	for(unsigned i = 0; i < sums.size(); i++){
		if(sums[i] < 0) {
			results.push_back(-1);
		} else {
			results.push_back(1);
			carrerIndex = i;
		}
	}
	return carrerIndex;
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

invocation_response create_success_response(int carrerId, string carrerName) {

    JsonValue carrer, resp;
    carrer.WithInteger("id", carrerId).WithString("name", carrerName);
    resp.WithInteger("status", 200).WithObject("carrer", carrer);

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

                int carrerIndex = run_ann_dio_careers(careerSurveyAnswers);
                string carrerName;
                switch (carrerIndex) {
                    case 1:
                        carrerName = "Carreira Back-end";
                        break;
                    case 2:
                        carrerName = "Carreira Front-end";
                        break;
                    case 3:
                        carrerName = "Carreira Mobile";
                        break;
                    case 4:
                        carrerName = "Carreira Infra, DevOps e Security";
                        break;
                    case 5:
                        carrerName = "Carreira Cloud";
                        break;
                    case 6:
                        carrerName = "Carreira Data e Analytics";
                        break;
                    case 7:
                        carrerName = "Carreira Games";
                        break;
                    case 8:
                        carrerName = "Carreira Qualidade de Software";
                        break;
                    case 9:
                        carrerName = "Carreira Web3 e IA";
                        break;
                    case 10:
                        carrerName = "Carreira Liderança e SoftSkill";
                        break;
                    case 11:
                        carrerName = "Carreira CRM";
                        break;
                    default:
                        return create_error_response("Não identificamos uma carreira ideal pra você. Responda novamente deixando suas preferências mais claras 😉");
                }
                return create_success_response(carrerIndex, carrerName);
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
